# Copyright (c) 1999-2014 OPEN CASCADE SAS
#
# This file is part of Open CASCADE Technology software library.
#
# This library is free software; you can redistribute it and/or modify it under
# the terms of the GNU Lesser General Public License version 2.1 as published
# by the Free Software Foundation, with special exception defined in the file
# OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
# distribution for complete text of the license and disclaimer of any warranty.
#
# Alternatively, this file may be used under the terms of Open CASCADE
# commercial license or contractual agreement.

;#
;# Liste des toolkits WOK sous forme de full path
;# 
proc ApplicationFramework:toolkits { } {
    return [list \
		PTKernel \
		TKPShape \
		TKCDF \
		TKLCAF \
                TKCAF \
                TKBinL \
                TKXmlL \
		TKShapeSchema \
                TKPLCAF \
                TKBin \
                TKXml \
		TKPCAF \
		FWOSPlugin \
		TKStdLSchema \
                TKStdSchema \
                TKTObj \
                TKBinTObj \
                TKXmlTObj \
           ]
}
;#
;# Autres UDs a prendre.
;#
proc ApplicationFramework:ressources { } {
    return [list  \
		[list both r StdResource {}] \
                [list both r XmlOcafResource {}] \
	       ]
}
;#
;# Nom du module 
;#
proc ApplicationFramework:name { } {
    return ApplicationFramework
}
;#
;# Short Nom du module  ( 3 lettres )
;#
proc ApplicationFramework:alias { } {
    return CAF
}
proc ApplicationFramework:depends { } {
    return [list Visualization]
}
;#
;# Pre-requis pour la compilation ( -I ... )
;# Returns a list of directory that should be used in -I directives
;# while compiling c or c++ files.
;#
proc ApplicationFramework:CompileWith { } {


    set l {}
    switch -- [OS:os] {
	HP-UX {
	}
	Linux {
	    lappend l "-I[lindex [wokparam -v %CSF_JavaHome] 0]/include"
	    lappend l "-I[lindex [wokparam -v %CSF_JavaHome] 0]/include/linux"
	    lappend l "[lindex [wokparam -v %CSF_TCL_HOME] 0]/include"
           lappend l "[lindex [lindex [wokparam -v %STLPortInclude] 0] 0]" 
	}
	SunOS {
	    lappend l "/usr/openwin/include"
	    lappend l "/usr/dt/include"
	    lappend l "[lindex [wokparam -v %CSF_CXX_INCLUDE] 0]"
	    lappend l "-I[lindex [wokparam -v %CSF_JavaHome] 0]/include"
	    lappend l "-I[lindex [wokparam -v %CSF_JavaHome] 0]/include/solaris"
	    lappend l "[lindex [wokparam -v %CSF_TCL_HOME] 0]/include"
	}

	IRIX {
	    lappend l "/usr/include/CC"
	}

    }
    return $l
}
;#
;# Pre-requis pour la compilation ( -L ... )
;# Returns a list of directory that should be used in -L directives
;# while creating shareable.
;#
proc ApplicationFramework:LinksoWith { } {


    set l {}
    switch -- [OS:os] {
	HP-UX {
	}
	Linux {
	    lappend l /usr/X11R6/lib
	}
	SunOS {
	    lappend l "-L[wokparam -v %CSF_TCL_HOME]/lib -R[wokparam -v %CSF_TCL_HOME]/lib -ltcl"
	    lappend l "-L[wokparam -v %CSF_TCL_HOME]/lib -R[wokparam -v %CSF_TCL_HOME]/lib -ltk"
	}
	IRIX  {
	    lappend l /usr/lib32 
	}
    }
    return $l
}
;#
;# Returns a list of exported features.
;# source : Source files
;# runtime: Shareables
;# wokadm : WOK admin files
;# api    : Public include files
;#
proc ApplicationFramework:Export { } {
    return [list source runtime wokadm api]
}
