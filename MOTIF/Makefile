
#HDRFILES = BMotif_defs.h BMotif_globals.c BMotif_globals.h

HDRFILES = \
 BMotif_defs.h \
 BMotif_globals.h \
 BMotif_BaseParameters.h

MOTIFBASE = \
 CFG_DEP_BASE/CDE/C/CfgDepBase.g \
 \
 CFG_DEP_BASE/CDE/C/file_dump.g \
 CFG_DEP_BASE/CDE/C/CfgDepCtx.g \
 CFG_DEP_BASE/CDE/C/CfgDepBaseCtx.g \
 CFG_DEP_BASE/CDE/C/Scalar_TYPE.g \
 CFG_DEP_BASE/CDE/C/Bool_TYPE.g \
 CFG_DEP_BASE/CDE/C/String_TYPE.g \
 CFG_DEP_BASE/CDE/C/basic_io.g \
 CFG_DEP_BASE/CDE/C/CfgDepBase_file_dump.g \
 \
 CFG_DEP_BASE/CDE/C/Abs2Conc_ffnc_ctx.c \
 CFG_DEP_BASE/CDE/C/CfgDepBase_seq_ctx.c \
 CFG_DEP_BASE/CDE/C/CfgDepBase_set_ctx.c \
 CFG_DEP_BASE/CDE/C/CfgDepBase_str_ctx.c \
 CFG_DEP_BASE/CDE/C/Construct_ffnc_ctx.c \
 CFG_DEP_BASE/CDE/C/GENState_ffnc_ctx.c \
 CFG_DEP_BASE/CDE/C/MRIState_ffnc_ctx.c \
 CFG_DEP_BASE/CDE/C/Seqstr_ffnc_ctx.c \
 CFG_DEP_BASE/CDE/C/String_ffnc_ctx.c \
 \
 CFG_DEP_BASE/CDE/C/CfgDepCtx.h

BEESRCFILES_MOTIF = \
 ../BEESRC/itfmch.c.motif \
 ../BEESRC/natmch.c.motif \
 ../BEESRC/filmch.c.motif \
 ../BEESRC/themch.c.motif \
 ../BEESRC/save_restore_bplatform_bin.c \
 ../BEESRC/save_restore_BTool_bin.c \
 ../BEESRC/tolmch.c.motif \
 ../BEESRC/symmch.c.motif \
 ../BEESRC/symmch.h \
 ../BEESRC/strmch.c.motif \
 ../BEESRC/lexmch.c.motif \
 ../BEESRC/frmmch.c.motif \
 ../BEESRC/errmch.c.motif \
 ../BEESRC/macmch.c.motif \
 ../BEESRC/rulmch.c.motif \
 ../BEESRC/resmch.c.motif \
 ../BEESRC/hypmch.c.motif \
 ../BEESRC/tacmch.c.motif \
 ../BEESRC/tacmch.h \
 ../BEESRC/nodmch.c.motif \
 ../BEESRC/golmch.c.motif \
 ../BEESRC/golmch.h \
 ../BEESRC/seqmch.c.motif

BEESRCFILES = \
 ../BEESRC/codmch.c \
 ../BEESRC/ctxmch.c \
 ../BEESRC/ficmch.c \
 ../BEESRC/fncmch.c \
 ../BEESRC/inimch.c \
 ../BEESRC/macros.c \
 ../BEESRC/outmch.c \
 ../BEESRC/setmch.c \
 ../BEESRC/shlmch.c \
 ../BEESRC/sysmch.c \
 ../BEESRC/timmch.c \
 ../BEESRC/trmmch.c \
 ../BEESRC/winmch.c \
 ../BEESRC/ysnmch.c

BEESRCBASE = \
 ../BEESRC/BTL_PRF/CDE/C/btl_proofCtx.g \
 ../BEESRC/BTL_PRF/CDE/C/btl_proof.g \
 ../BEESRC/BTL_PRF/CDE/C/btl_proof_file_dump.g \
 \
 ../BEESRC/BTL_PRF/CDE/C/btl_proofCtx.h \
 ../BEESRC/BTL_PRF/CDE/C/btl_proof.h \
 ../BEESRC/BTL_PRF/CDE/C/btl_proof_file_dump.h

#################################################################

   $(BKIT)/BLIB/BMotif :    BMotif.o \
                            BMotif_globals.o \
                            BMotif_browser.o \
                            BMotif_fifo.o \
                            BMotif_init.o \
                            BMotif_io.o \
                            BMotif_utils.o \
                            BMotif_widgets.o \
                            BMotif_displaystate.o \
                            appmch.motif.o \
                            motif.o \
                            bmotif_sub.o \
                            bmotif.o \
                            BToolkitlm_globals.o \
                            ClientSocket.o \
                            BMotif.resources
	../UTIL/_link_BMotif
	@echo
	@echo "  make complete"
	@echo

   BMotif.o :               BMotif.c \
                            $(MOTIFBASE) \
                            $(HDRFILES)
	../UTIL/_compile_file BMotif

   BMotif_globals.o :       BMotif_globals.c \
                            BMotif_version.c BMotif_help.c \
                            $(HDRFILES)
	../UTIL/_compile_file BMotif_globals

   BMotif_browser.o :       BMotif_browser.c \
                            BMotif_version.c \
                            $(HDRFILES)
	../UTIL/_compile_file BMotif_browser

   BMotif_fifo.o :          BMotif_fifo.c \
                            $(HDRFILES)
	../UTIL/_compile_file BMotif_fifo

   BMotif_init.o :          BMotif_init.c \
                            $(HDRFILES)
	../UTIL/_compile_file BMotif_init

   BMotif_io.o :            BMotif_io.c \
                            BMotif_version.c \
                            ../C/BToolkitlm_globals.h \
                            ../C/BToolkitd_common.c \
                            $(HDRFILES)
	../UTIL/_compile_file BMotif_io

   BMotif_utils.o :         BMotif_utils.c \
                            $(HDRFILES)
	../UTIL/_compile_file BMotif_utils

   BMotif_widgets.o :       BMotif_widgets.c \
                            BMotif_version.c \
                            $(HDRFILES)
	../UTIL/_compile_file BMotif_widgets

   BMotif_displaystate.o :  BMotif_displaystate.c \
                            BMotif_version.c \
                            $(HDRFILES)
	../UTIL/_compile_file BMotif_displaystate

   BToolkitlm_globals.o :   ../C/BToolkitlm_globals.h \
                            ../C/BToolkitlm_globals.c
	../UTIL/_compile_file ../C/BToolkitlm_globals

   appmch.motif.o :         ../BEESRC/appmch.motif.c \
                            ../BEESRC/motif.h \
                            ../BEESRC/bmotif.h \
                            ../BEESRC/ctxmch.h \
                            ../BEESRC/symmch.h \
                            ../BEESRC/golmch.h \
                            $(HDRFILES)
	../UTIL/_compile_file ../BEESRC/appmch.motif

   motif.o :                ../BEESRC/motif.c \
                            ../BEESRC/bmotif.h \
                            ../BEESRC/ctxmch.h \
                            ../BEESRC/symmch.h \
                            ../BEESRC/golmch.h \
                            $(BEESRCBASE) \
                            $(HDRFILES)
	../UTIL/_compile_file ../BEESRC/motif

   bmotif_sub.o :           ../BEESRC/bmotif_sub.c \
                            $(BEESRCFILES_MOTIF) \
                            $(BEESRCFILES) \
                            $(HDRFILES)
	../UTIL/_copy_motif_to_c
	../UTIL/_compile_file ../BEESRC/bmotif_sub
	../UTIL/_rem_copied_to_c

   bmotif.o :               ../BEESRC/bmotif.c \
                            ../BEESRC/prfmch.c.motif \
                            ../BEESRC/motif.h \
                            ../BEESRC/bmotif.h \
                            ../BEESRC/appmch.motif.h \
                            ../BEESRC/ctxmch.h \
                            ../BEESRC/symmch.h \
                            ../BEESRC/golmch.h \
                            ../BEESRC/tacmch.h \
                            $(HDRFILES)
	../UTIL/_compile_file ../BEESRC/bmotif

   ClientSocket.o :         ../C/ClientSocket.c \
                            ../C/BToolkitlm_globals.h \
                            ../C/BToolkitd_ClientServer/CDE/C/BToolkitd_Client_Client.g \
                            ../C/BToolkitd_ClientServer/CDE/C/BToolkitd_Client_Client.c \
                            $(HDRFILES)
	../UTIL/_compile_file ../C/ClientSocket

   BMotif.resources :       ../MOTIF/BMotif.resources
	cp ../MOTIF/BMotif.resources ~/XBMotif

