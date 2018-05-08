GEN_PIXBUF_CSOURCE = gen-pixbuf-csource

IMAGES = dh.ico mail.bmp udo.ico udosh.ico weblink.bmp

EXTRA_DIST = \
	$(IMAGES) \
	dh.h mail.h udo.h udosh.h weblink.h

images: $(IMAGES)
	if test "`type $(GEN_PIXBUF_CSOURCE) 2>/dev/null`" = ""; then \
		echo "$(GEN_PIXBUF_CSOURCE) not found" >&2; \
	else \
		$(GEN_PIXBUF_CSOURCE) --raw --name dh_data dh.ico > dh.h; \
		$(GEN_PIXBUF_CSOURCE) --raw --name email_data mail.bmp > mail.h; \
		$(GEN_PIXBUF_CSOURCE) --raw --name udo_data udo.ico > udo.h; \
		$(GEN_PIXBUF_CSOURCE) --raw --name udosh_data udosh.ico > udosh.h; \
		$(GEN_PIXBUF_CSOURCE) --raw --name weblink_data weblink.bmp > weblink.h; \
	fi
