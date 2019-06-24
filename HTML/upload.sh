cd cgi-bin
gcc -o login.cgi login.c
scp login.cgi srcserver:/var/www/cgi-bin/
cd ..
scp Index.html srcserver:/var/www/html/
scp map.html srcserver:/var/www/html/