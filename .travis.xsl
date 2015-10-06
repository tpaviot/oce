<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

   <xsl:strip-space elements="*"/>
   <xsl:output method="text"/>

   <xsl:param name="duration"/>

   <xsl:template match="testsuite">
       <xsl:choose>
           <xsl:when test="$duration = 1">
               <xsl:value-of select="@name"/>
               <xsl:text> (</xsl:text>
               <xsl:value-of select="@tests"/>
               <xsl:text> tests, </xsl:text>
               <xsl:value-of select="@skipped"/>
               <xsl:text> skipped, </xsl:text>
               <xsl:value-of select="@failures"/>
               <xsl:text> failures, </xsl:text>
               <xsl:value-of select="@errors"/>
               <xsl:text> errors) </xsl:text>
               <xsl:value-of select="format-number(@time, '###.##s')"/><xsl:text>
</xsl:text>
           </xsl:when>
           <xsl:otherwise>
               <xsl:apply-templates select="testcase"/>
           </xsl:otherwise>
       </xsl:choose>
   </xsl:template>

   <xsl:template match="testcase">
       <xsl:if test="contains(@status, 'FAILED')">
           <xsl:variable name="parent" select="../@name"/>
           <xsl:value-of select="translate($parent, ' ', '/')"/>/<xsl:value-of select="@name"/>
           <xsl:text>
</xsl:text>
       </xsl:if>
   </xsl:template>

</xsl:stylesheet>

