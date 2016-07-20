
default:	build

clean:
	rm -rf Makefile objs

build:
	$(MAKE) -f objs/Makefile
	$(MAKE) -f objs/Makefile manpage

install:
	$(MAKE) -f objs/Makefile install

upgrade:
	/home/godman/nginx-1.8.1/sbin/nginx -t

	kill -USR2 `cat /home/godman/nginx-1.8.1/logs/nginx.pid`
	sleep 1
	test -f /home/godman/nginx-1.8.1/logs/nginx.pid.oldbin

	kill -QUIT `cat /home/godman/nginx-1.8.1/logs/nginx.pid.oldbin`
