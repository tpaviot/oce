<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

   <xsl:strip-space elements="*"/>
   <xsl:output method="text"/>

   <xsl:template match="testcase">
       <xsl:if test="@status != 'OK'">
           <xsl:variable name="parent" select="../@name"/>
           <xsl:value-of select="translate($parent, ' ', '/')"/>/<xsl:value-of select="@name"/>
           <xsl:text> </xsl:text><xsl:value-of select="@status"/><xsl:text>
</xsl:text>
       </xsl:if>
   </xsl:template>

</xsl:stylesheet>

