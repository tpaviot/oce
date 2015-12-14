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
proc DataExchange:toolkits { } {
    return [list TKXSBase TKSTEPBase TKSTEPAttr TKSTEP209 TKSTEP TKIGES \
		TKXCAF TKXCAFSchema TKXDEIGES TKXDESTEP \
		TKSTL TKVRML TKXmlXCAF TKBinXCAF]
}
;#
;# Autres UDs a prendre.
;#
proc DataExchange:ressources { } {
    return [list  \
	    [list both r XSMessage {} ] \
	    [list both r SHMessage {} ] \
	    [list both r XSTEPResource {} ] \
	    ]
}
;#
;# retourne une liste de triplets {type <full path1> <target directory>/name}
;# permet de faire : cp <full path> $CASROOT/<target directory>/name
;# On peut ainsi embarquer des fichiers d'un peu partout et les dispatcher sous 
;# la racine d'arrivee et ce avec un autre nom.
;# rien n'empeche de CALCULER automatiquement des paths dans cette proc.
;# type = source/runtime/both pour dire si le fichier va dans l'archive en question.
;# une deux (ou les deux) type d'archive fabriquees. 
;#
proc DataExchange:freefiles { } {
    return {}
}
;#
;# Nom du module 
;#
proc DataExchange:name { } {
    return DataExchange
}
proc DataExchange:alias { } {
    return DXE
}
proc DataExchange:depends { } {
    return [list ApplicationFramework]
}
;#
;# Liste des includes utilises qui ne sont pas ceux des Wb.
;#
proc DataExchange:CompileWith { } {
    
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
proc DataExchange:LinksoWith { } {
    
    set l {}
    switch -- [OS:os] {
	HP-UX {
	}
	Linux {
	}
	SunOS {
	    lappend l "-L[wokparam -v %CSF_TCL_HOME]/lib -R[wokparam -v %CSF_TCL_HOME]/lib -ltcl"
	    lappend l "-L[wokparam -v %CSF_TCL_HOME]/lib -R[wokparam -v %CSF_TCL_HOME]/lib -ltk"
	}
	IRIX {
	    lappend l "/usr/lib32"
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
proc DataExchange:Export { } {
    return [list source runtime wokadm api]
}
