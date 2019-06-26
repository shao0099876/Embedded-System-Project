cd cgi-bin
gcc -o login.cgi login.c
gcc -o refreshpos.cgi refreshpos.c
gcc -o getpointlist.cgi getpointlist.c
gcc -o addpoint.cgi addpoint.c
gcc -o delpoint.cgi delpoint.c
scp login.cgi srcserver:/var/www/cgi-bin/
scp refreshpos.cgi srcserver:/var/www/cgi-bin/
scp getpointlist.cgi srcserver:/var/www/cgi-bin/
scp addpoint.cgi srcserver:/var/www/cgi-bin/
scp delpoint.cgi srcserver:/var/www/cgi-bin/
cd ..
scp Index.html srcserver:/var/www/html/
scp map.html srcserver:/var/www/html/
scp area.html srcserver:/var/www/html/
scp editpoint.html srcserver:/var/www/html/