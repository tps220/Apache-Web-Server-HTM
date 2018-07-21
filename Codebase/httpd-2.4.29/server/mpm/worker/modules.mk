mod_mpm_worker.la: worker.slo fdqueue.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version worker.lo fdqueue.lo
DISTCLEAN_TARGETS = modules.mk
static =
shared = mod_mpm_worker.la
