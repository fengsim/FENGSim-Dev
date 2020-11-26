Github use the **Markdown** language to edit website and wiki.

### The installation of Github
`sudo apt-get install git`

### The installation of Gollum
* `git clone https://github.com/fengsim/FENGSim-Dev.wiki.git`
* `sudo docker pull genebarker/gollum`
* `sudo docker run -d -p 80:80 -v ~/mywiki:/root/wiki genebarker/gollum --http`

By using localhost or 127.0.0.1, we could edit wiki from github by using gollum locally.