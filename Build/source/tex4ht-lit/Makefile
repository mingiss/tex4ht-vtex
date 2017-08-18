# $Id: Makefile 113 2013-10-07 17:18:13Z karl $
# This file is public domain.  Originally written 2010, Karl Berry.
# 
# todo: look for xx below

wd = work.dir
tex_opts = --interaction=nonstopmode #--file-line-error
tex_1opt = "$(tex_opts)"
tex_runner = vtex 2010 tex
tex_runer = vtex 2010 tex
latex_runner = vtex 2010 latex
htlatex_runner = vtex 2010 4ht htlatex
xhlatex_runner = vtex 2010 4ht xhlatex

default: all

common = tex4ht-cpright.tex common.tex common-code.tex
common_info = $(common) common-info.tex
derived = 

derived += $(tex4ht_4ht_derived)
tex4ht_4ht_derived = book.4ht
# and many, many more.

derived += $(tex4ht_bibtex2_derived)
tex4ht_bibtex2_derived = bibtex2.4ht

derived += $(tex4ht_c_derived)
tex4ht_c_derived = tex4ht.c

derived += $(tex4ht_cond4ht_derived)
tex4ht_cond4ht_derived = cond4ht.4ht mktex4ht.4ht

derived += $(tex4ht_docbook_xtpipes_derived)
tex4ht_docbook_xtpipes_derived = docbook.4xt DbUtilities.java

derived += $(tex4ht_docbook_derived)
tex4ht_docbook_derived = docbook.4ht docbook-math.4ht docbook-mml.4ht

derived += $(tex4ht_env_derived)
tex4ht_env_derived = tex4ht.env-unix tex4ht.env-win32 tex4ht.env

derived += $(tex4ht_fonts_cjk_derived)
tex4ht_fonts_cjk_derived = tex4ht-fonts-cjk.html # and lots more

derived += $(tex4ht_fonts_cjk_utf8_derived)
tex4ht_fonts_cjk_utf8_derived = tex4ht-fonts-cjk-utf8.html # and lots more

derived += $(tex4ht_fonts_noncjk_derived)
tex4ht_fonts_noncjk_derived = SearchFonts.java cmtex.htf # and lots more
# also, whither lm-htf.tex?  whither tmp?  how change target dir?

# htcmd not used
#derived += $(tex4ht_htcmd_derived)
#tex4ht_htcmd_derived = htcmd.c

derived += $(tex4ht_html_speech_xtpipes_derived)
tex4ht_html_speech_xtpipes_derived = htspk.4xt HtSpk.java

derived += $(tex4ht_html_speech_derived)
tex4ht_html_speech_derived = html-speech.4ht html-speech-math.4ht emacspeak.4ht

derived += $(tex4ht_html0_derived)
tex4ht_html0_derived = html0.4ht

derived += $(tex4ht_html32_derived)
tex4ht_html32_derived = html32.4ht html32-math.4ht 

#xx derived += $(tex4ht_html4_derived)
tex4ht_html4_derived = \
  html4.4ht html4-math.4ht html4-uni.4ht onmouseover.4ht exerqz.4ht

derived += $(tex4ht_info_mml_derived)
tex4ht_info_mml_derived = infomml.4ht

derived += $(tex4ht_info_ooffice_derived)
tex4ht_info_ooffice_derived = infoof.4ht

derived += $(tex4ht_info_svg_derived)
tex4ht_info_svg_derived = infosvg.4ht

#xx derived += $(tex4ht_info_derived)
tex4ht_info_derived = info4ht.4ht

derived += $(tex4ht_javahelp_xtpipes_derived)
tex4ht_javahelp_xtpipes_derived = javahelp.4xt

derived += $(tex4ht_javahelp_derived)
tex4ht_javahelp_derived = javahelp.4ht javahelp-a.4ht

derived += $(tex4ht_jsmath_derived)
tex4ht_jsmath_derived = jsmath.4ht html-jsmath.4ht

derived += $(tex4ht_jsml_xtpipes_derived)
tex4ht_jsml_xtpipes_derived = \
  jsml.4xt \
  HtJsml.java GroupMn.java JsmlFilter.java JsmlMathBreak.java

derived += $(tex4ht_jsml_derived)
tex4ht_jsml_derived = jsml.4ht jsml-math.4ht

derived += $(tex4ht_mathltx_derived)
tex4ht_mathltx_derived = mathltx.4ht html-mltx.4ht

derived += $(tex4ht_mathplayer_derived)
tex4ht_mathplayer_derived = mathplayer.4ht

derived += $(tex4ht_mkht_derived)
tex4ht_mkht_derived = mkht.4ht mk4ht.perl mkht-scripts.4ht

derived += $(tex4ht_moz_derived)
tex4ht_moz_derived = mozilla.4ht

derived += $(tex4ht_oo_xtpipes_derived)
tex4ht_oo_xtpipes_derived = \
   oo-math.4xt oo-text.4xt \
   OoUtilities.java OomFilter.java OoFilter.java

derived += $(tex4ht_ooffice_derived)
tex4ht_ooffice_derived = ooffice.4ht ooffice-mml.4ht

derived += $(tex4ht_ooimpress_derived)
tex4ht_ooimpress_derived = ooimpress.4ht

derived += $(tex4ht_options_derived)
tex4ht_options_derived = tex4ht.4ht

derived += $(tex4ht_svg_derived)
tex4ht_svg_derived = svg.4ht html4-svg.4ht

derived += $(tex4ht_t4ht_derived)
tex4ht_t4ht_derived = t4ht.c

derived += $(tex4ht_tei_derived)
tex4ht_tei_derived = tei.4ht tei-mml.4ht tei-math.4ht tei-mmltei.4ht

derived += $(tex4ht_unicode_derived)
tex4ht_unicode_derived = unicode.4ht

derived += $(tex4ht_word_derived)
tex4ht_word_derived = htmlw.4ht

derived += $(tex4ht_xhtml_xtpipes_derived)
tex4ht_xhtml_xtpipes_derived = xhtml.4xt XhtmlEmails.java

derived += $(tex4ht_xhtmml_xtpipes_derived)
tex4ht_xhtmml_xtpipes_derived = xhtmml.4xt XhtmmlUtilities.java

# wripro.tex generates nothing (not literate).

derived += $(xtpipes_derived)
xtpipes_derived = \
  $(wd)/xtpipes.java \
  $(wd)/xtpipes/FileInfo.java \
  $(wd)/xtpipes/InputObject.java \
  $(wd)/xtpipes/Xtpipes.java \
  $(wd)/xtpipes/XtpipesPrintWriter.java \
  $(wd)/xtpipes/XtpipesUni.java \
  $(wd)/xtpipes/util/ScriptsManager.java \
  $(wd)/xtpipes/util/ScriptsManagerLH.java \
  xtpipes-default.4xt \
  xtpipes-map.dtd \
  xtpipes.dtd \

# 
all: $(derived)

$(tex4ht_4ht_derived): tex4ht-4ht.tex $(common)
	$(tex_runer) $(tex_opts) $<

$(tex4ht_bibtex2_derived): tex4ht-bibtex2.tex $(common)
	$(latex_runner) $(tex_opts) $<

$(tex4ht_c_derived): tex4ht-c.tex $(common)
	$(tex_runer) $(tex_opts) $<

$(tex4ht_cond4ht_derived): tex4ht-cond4ht.tex $(common)
	$(tex_runer) $(tex_opts) $<
	$(tex_runer) $(tex_opts) cond4ht.4ht

$(tex4ht_docbook_xtpipes_derived): tex4ht-docbook-xtpipes.tex $(common)
	$(xhlatex_runner) $< "html,3" "" "-d./" $(tex_1opt)

$(tex4ht_docbook_derived): tex4ht-docbook.tex $(common)
	$(xhlatex_runner) $< "html,3" "" "-d./" $(tex_1opt)

$(tex4ht_env_derived): tex4ht-env.tex $(common)
	$(htlatex_runner) $< "xhtml,3" "" "-d./" $(tex_1opt)

$(tex4ht_fonts_cjk_derived): tex4ht-fonts-cjk.tex
	ht tex $<

$(tex4ht_fonts_cjk_utf8_derived): tex4ht-fonts-cjk-utf8.tex
	ht tex $<

$(tex4ht_fonts_noncjk_derived): \
  tex4ht-fonts-noncjk.tex tex4ht-fonts-modern.tex $(common)
	ht tex $<

$(tex4ht_htcmd_derived): tex4ht-htcmd.tex $(common)
	ht tex $<

$(tex4ht_html_speech_xtpipes_derived): tex4ht-html-speech-xtpipes.tex $(common)
	$(htlatex_runner) $< "html,next,3" "" "-d./" $(tex_1opt)

$(tex4ht_html_speech_derived): tex4ht-html-speech.tex $(common)
	$(xhlatex_runner) $< "html,3,sections+" "" "-d./" $(tex_1opt)

$(tex4ht_html0_derived): tex4ht-html0.tex $(common)
	$(xhlatex_runner) $< "html,3,sections+" "" "-d./" $(tex_1opt)

$(tex4ht_html32_derived): tex4ht-html32.tex $(common)
	$(xhlatex_runner) $< "html,3,sections+" "" "-d./" $(tex_1opt)

$(tex4ht_html4_derived): tex4ht-html4.tex $(common)
	$(htlatex_runner) $< "html,sections+" "" "-d./" $(tex_1opt)

$(tex4ht_info_mml_derived): tex4ht-info-mml.tex $(common_info)
	$(htlatex_runner) $< "html,sections+" "" "-d./" $(tex_1opt)

$(tex4ht_info_ooffice_derived): tex4ht-info-ooffice.tex $(common_info)
	$(htlatex_runner) $< "html,sections+" "" "-d./" $(tex_1opt)

$(tex4ht_info_svg_derived): tex4ht-info-svg.tex $(common_info)
	$(htlatex_runner) $< "html,sections+" "" "-d./" $(tex_1opt)

$(tex4ht_info_derived): tex4ht-info.tex $(common)
	$(xhlatex_runner) $< "html,3,sections+" "" "-d./" $(tex_1opt)

$(tex4ht_javahelp_xtpipes_derived): tex4ht-javahelp-xtpipes.tex $(common)
	$(htlatex_runner) $< "xhtml,next,3" "" "-d./" $(tex_1opt)

$(tex4ht_javahelp_derived): tex4ht-javahelp.tex $(common)
	$(xhlatex_runner) $< "html,3,sections+" "" "-d./" $(tex_1opt)

$(tex4ht_jsmath_derived): tex4ht-jsmath.tex $(common)
	$(xhlatex_runner) $< "html,3,sections+" "" "-d./" $(tex_1opt)

$(tex4ht_jsml_xtpipes_derived): tex4ht-jsml-xtpipes.tex $(common)
	$(htlatex_runner) $< "xhtml,next,3" "" "-d./" $(tex_1opt)

$(tex4ht_jsml_derived): tex4ht-jsml.tex $(common)
	$(xhlatex_runner) $< "html,3,sections+" "" "-d./" $(tex_1opt)

$(tex4ht_mathltx_derived): tex4ht-mathltx.tex $(common)
	$(xhlatex_runner) $< "html,3,sections+" "" "-d./" $(tex_1opt)

$(tex4ht_mathplayer_derived): tex4ht-mathplayer.tex $(common)
	$(xhlatex_runner) $< "html,3,sections+" "" "-d./" $(tex_1opt)

$(tex4ht_mkht_derived): tex4ht-mkht.tex $(common)
	$(latex_runner) $(tex_opts) $<
	perl -c mk4ht.perl  # syntax check
	$(latex_runner) $(tex_opts) mkht-scripts.4ht

$(tex4ht_moz_derived): tex4ht-moz.tex $(common)
	$(xhlatex_runner) $< "html,3,sections+" "" "-d./" $(tex_1opt)

$(tex4ht_oo_xtpipes_derived): tex4ht-oo-xtpipes.tex $(common)
	$(htlatex_runner) $< "xhtml,next,3" "" "-d./" $(tex_1opt)

$(tex4ht_ooffice_derived): tex4ht-ooffice.tex $(common)
	$(htlatex_runner) $< "xhtml,4,sections+" "" "-d./" $(tex_1opt)

$(tex4ht_ooimpress_derived): tex4ht-ooimpress.tex $(common)
	$(htlatex_runner) $< "xhtml,4,sections+" "" "-d./" $(tex_1opt)

$(tex4ht_options_derived): tex4ht-options.tex $(common)
	mk4ht xhlatex $<

$(tex4ht_sty_derived): tex4ht-sty.tex $(common)
	ht tex $<

$(tex4ht_svg_derived): tex4ht-svg.tex $(common)
	$(xhlatex_runner) $< "html,3,sections+" "" "-d./" $(tex_1opt)

$(tex4ht_t4ht_derived): tex4ht-t4ht.tex $(common)
	ht tex $<

$(tex4ht_tei_derived): tex4ht-tei.tex $(common)
	$(xhlatex_runner) $< "html,3,sections+" "" "-d./" $(tex_1opt)

$(tex4ht_unicode_derived): tex4ht-unicode.tex $(common)
	$(xhlatex_runner) $< "html,3,sections+" "" "-d./" $(tex_1opt)

$(tex4ht_word_derived): tex4ht-word.tex $(common)
	$(xhlatex_runner) $< "html,3,sections+" "" "-d./" $(tex_1opt)

$(tex4ht_xhtml_xtpipes_derived): tex4ht-xhtml-xtpipes.tex $(common)
	$(htlatex_runner) $< "xhtml,3,next" "" "-d./" $(tex_1opt)

$(tex4ht_xhtmml_xtpipes_derived): tex4ht-xhtmml-xtpipes.tex $(common)
	$(htlatex_runner) $< "xhtml,3,next" "" "-d./" $(tex_1opt)

$(xtpipes_derived): xtpipes.tex $(common)
	$(htlatex_runner) $< "xhtml,3,next" "" "-d./" $(tex_1opt)
# Derived files are generated in . and $(wd).
# (corresponds to src/java for xtpipes.tex)

# 
destdir = ..
dest_texmf = $(destdir)/texmf/tex/generic/tex4ht
dest_4ht = $(destdir)/texmf/tex4ht
dest_base = $(dest_4ht)/base
dest_xtpipes = $(dest_4ht)/xtpipes
dest_src = $(destdir)/src
dest_java = $(dest_src)/java
#
update = cp -pr
mkdir = install -d
#
update: all
	$(update) $(tex4ht_bibtex2_derived) $(dest_src)/
#
	$(update) $(tex4ht_c_derived) $(dest_src)/
#
	$(update) $(tex4ht_cond4ht_derived) $(dest_texmf)/
#
	$(update) docbook.4xt $(dest_xtpipes)/
	$(update) DbUtilities.java $(dest_java)/
#
	$(update) $(tex4ht_docbook_derived) $(dest_texmf)/
#
	$(mkdir) $(dest_base)/unix $(dest_base)/win32
	$(update) tex4ht.env-unix $(dest_base)/unix/
	$(update) tex4ht.env-win32 $(dest_base)/win32/
#
	$(update) $(tex4ht_html_speech_xtpipes_derived) $(dest_texmf)/
#
	$(update) $(tex4ht_html_speech_derived) $(dest_texmf)/
#
	$(update) $(tex4ht_html0_derived) $(dest_texmf)/
#
	$(update) $(tex4ht_html32_derived) $(dest_texmf)/
#
	$(update) $(tex4ht_html4_derived) $(dest_texmf)/
#
	$(update) $(tex4ht_info_mml_derived) $(dest_texmf)/
#
	$(update) $(tex4ht_info_ooffice_derived) $(dest_texmf)/
#
	$(update) $(tex4ht_info_svg_derived) $(dest_texmf)/
#
	$(update) $(tex4ht_info_derived) $(dest_texmf)/
#
	$(update) $(tex4ht_javahelp_xtpipes_derived) $(dest_texmf)/
#
	$(update) $(tex4ht_javahelp_derived) $(dest_texmf)/
#
	$(update) $(tex4ht_jsmath_derived) $(dest_texmf)/
#
	$(update) jsml.4xt $(dest_xtpipes)/
	$(update) HtJsml.java GroupMn.java JsmlFilter.java \
	          JsmlMathBreak.java $(dest_java)/
#
	$(update) $(tex4ht_jsml_derived) $(dest_texmf)/
#
	$(update) $(tex4ht_mathltx_derived) $(dest_texmf)/
#
	$(update) $(tex4ht_mathplayer_derived) $(dest_texmf)/
#
	$(update) $(tex4ht_moz_derived) $(dest_texmf)/
#
	$(update) oo-text.4xt oo-math.4xt $(dest_xtpipes)/
	$(update) OoUtilities.java OomFilter.java $(dest_java)/
#
	$(update) $(tex4ht_ooffice_derived) $(dest_texmf)/
#
	$(update) $(tex4ht_ooimpress_derived) $(dest_texmf)/
#
	$(update) $(tex4ht_options_derived) $(dest_texmf)/
#
	$(update) $(tex4ht_sty_derived) $(dest_texmf)/
#
	$(update) $(tex4ht_svg_derived) $(dest_texmf)/
#
	$(update) $(tex4ht_t4ht_derived) $(dest_src/
#
	$(update) $(tex4ht_tei_derived) $(dest_texmf)/
#
	$(update) $(tex4ht_unicode_derived) $(dest_texmf)/
#
	$(update) $(tex4ht_word_derived) $(dest_texmf)/
#
	$(update) xhtml.4xt $(dest_xtpipes)/
	$(update) XhtmlEmails.java $(dest_java)/
#
	$(update) xhtmml.4xt $(dest_xtpipes)/
	$(update) XhtmmlUtilities.java $(dest_java)/
#
# this has to be done last. Does anything else use $(wd)? We'll see.
	rmdir $(wd)/bin
	$(update) $(wd)/* $(dest_java)/
	$(update) xtpipes.dtd xtpipes-map.dtd xtpipes-default.4xt 
	  $(dest_xtpipes)/

clean: mostlyclean
	rm -rf $(wd)
	rm -f *.4ct *.4tc *.aux *.css *.dvi *.idv *.lg *.log *.tmp *.trc *.xref
	rm -f *.4es *.bat *.unix *.htf *.html *.png tmp

clean1:
	rm -f $(f).[0-s]* $(f).[u-z]* $(f).trc

mostlyclean:
	rm -f $(derived)
