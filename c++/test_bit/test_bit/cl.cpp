#include "StdAfx.h"
#include "cl.h"


bool cl::isBold() 
{
   return bold;
}

bool cl::isItalic() 
{
   return italic;
}

bool cl::isUnderline() 
{
   return underline;
}

bool cl::isStrikethrough() 
{
   return strikethrough;
}

bool cl::isSubscript() 
{
   return subscript;
}

bool cl::isSuperscript() 
{
   return superscript;
}

void cl::setBold(bool state) 
{
   bold = state;
}

void cl::setItalic(bool state) 
{
   italic = state;
}

void cl::setUnderline(bool state) 
{
   underline = state;
}

void cl::setStrikethrough(bool state) 
{
   strikethrough = state;
}

void cl::setSubscript(bool state) 
{
   subscript = state;
}

void cl::setSuperscript(bool state) 
{
   superscript = state;
}

bool cl::operator!=(cl & obj)
{
   if (this->bold != obj.bold)
   {
      return true;
   }
   if (this->italic != obj.italic)
   {
      return true;
   }
   if (this->underline != obj.underline)
   {
      return true;
   }
   if (this->strikethrough != obj.strikethrough)
   {
      return true;
   }
   if (this->subscript != obj.subscript)
   {
      return true;
   }
   if (this->superscript != obj.superscript)
   {
      return true;
   }

   return false;
}
