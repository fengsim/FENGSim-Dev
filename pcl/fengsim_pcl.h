#include <pcl/point_types.h>
#include <fstream>

void export_pc_to_vtk (pcl::PointCloud<pcl::PointXYZ> pc, std::string filename)
{
    std::ofstream out(filename);
    for (int i = 0; i < pc.size(); i++) {
        out << (pc.points)[i].x << " "
	    << (pc.points)[i].y << " "
	    << (pc.points)[i].z << std::endl;
    }
    out.close();
}

void import_pc (std::string filename, pcl::PointCloud<pcl::PointXYZ>::Ptr pc) {
    std::ifstream is(filename);
    const int len = 256;
    char L[len];
    while (is.getline(L,len)) {
        double z[3];
	sscanf(L,"%lf %lf %lf", z, z+1, z+2);
	pc->push_back(pcl::PointXYZ(z[0], z[1], z[2]));
    }
    is.close();
}

void voxel_grid (pcl::PointCloud<pcl::PointXYZ>& pc, double t, std::string filename) {
    double xmax = (pc.points)[0].x;
    double ymax = (pc.points)[0].y;
    double zmax = (pc.points)[0].z;
    double xmin = (pc.points)[0].x;
    double ymin = (pc.points)[0].y;
    double zmin = (pc.points)[0].z;
    for (int i = 0; i < pc.size(); i++) {
        if ((pc.points)[i].x > xmax) xmax = (pc.points)[i].x;
	if ((pc.points)[i].y > ymax) ymax = (pc.points)[i].y;
	if ((pc.points)[i].z > zmax) zmax = (pc.points)[i].z;
	
	if ((pc.points)[i].x < xmin) xmin = (pc.points)[i].x;
	if ((pc.points)[i].y < ymin) ymin = (pc.points)[i].y;
	if ((pc.points)[i].z < zmin) zmin = (pc.points)[i].z;
    }
    int nx = std::ceil((xmax - xmin) / t);
    int ny = std::ceil((ymax - ymin) / t);
    int nz = std::ceil((zmax - zmin) / t);
    nx++;
    ny++;
    nz++;
    std::cout << std::endl << "box numbers: " << nx << " " << ny << " " << nz << std::endl << std::endl;
    
    for (int i = 0; i < pc.size(); i++) {
        std::cout << "coordinates: " << (pc.points)[i].x << " " << (pc.points)[i].y << " " << (pc.points)[i].z << std::endl;
        std::cout << "box id: " << static_cast<int> (std::floor ((pc.points)[i].x / t)) << " ";
	std::cout << static_cast<int> (std::floor ((pc.points)[i].y / t)) << " ";
	std::cout << static_cast<int> (std::floor ((pc.points)[i].z / t)) << std::endl;
	double x,y,z;
	x = static_cast<int> (std::floor ((pc.points)[i].x / t)) + 0.5;
	y = static_cast<int> (std::floor ((pc.points)[i].y / t)) + 0.5;
	z = static_cast<int> (std::floor ((pc.points)[i].z / t)) + 0.5;
	std::cout << "distance to box center: " << std::sqrt(pow((pc.points)[i].x-x,2) + pow((pc.points)[i].y-y,2) + pow((pc.points)[i].z-z,2)) << std::endl << std::endl;
    }


    
    std::ofstream out(filename);
    out << "# vtk DataFile Version 2.0" << std::endl;
    out << "Rectilinear Grid by FENGSim" << std::endl;
    out << "ASCII" << std::endl;
    out << "DATASET RECTILINEAR_GRID" << std::endl;
    out << "DIMENSIONS " << nx+1 << " " << ny+1 << " " << nz+1 << std::endl;
    out << "X_COORDINATES " << nx+1 << " float" << std::endl;
    for (int i=0; i<nx+1; i++) {
        out << xmin + i*t << " ";
    }
    out << std::endl;
    out << "Y_COORDINATES " << ny+1 << " float" << std::endl;
    for (int i=0; i<ny+1; i++) {
        out << ymin + i*t << " ";
    }
    out << std::endl;
    out << "Z_COORDINATES " << nz+1 << " float" << std::endl;
    for (int i=0; i<nz+1; i++) {
        out << zmin + i*t << " ";
    }
    out << std::endl;
    out.close();
}

