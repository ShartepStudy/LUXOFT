#pragma once
class cl 
{
public:
//   cl():
//      f(25) {};
   //   italic(0),
   //   underline(0),
   //   strikethrough(0),
   //   subscript(0),
   //   superscript(0) {};
   //explicit cl(cl * const oFontStyle):
   //   bold(oFontStyle->isBold()),
   //   italic(oFontStyle->isItalic()),
   //   underline(oFontStyle->isUnderline()),
   //   strikethrough(oFontStyle->isStrikethrough()),
   //   subscript(oFontStyle->isSubscript()),
   //   superscript(oFontStyle->isSuperscript()) {};
   bool isBold() { return true; };
   bool isItalic() { return true; };
   bool isUnderline() { return true; };
	bool isStrikethrough() { return true; };
	bool isSubscript() { return true; };
	bool isSuperscript() { return true; };
   void setBold(bool state) {};
   void setItalic(bool state) {};
   void setUnderline(bool state) {};
   void setStrikethrough(bool state) {};
   void setSubscript(bool state) {};
   void setSuperscript(bool state) {};
   bool operator!=(cl & obj) { return true; };
   char f;
private:  
	/*unsigned bold           : 1;
	unsigned italic         : 1;
	unsigned underline      : 1;
	unsigned strikethrough  : 1;
	unsigned subscript      : 1;
	unsigned superscript    : 1;*/
};

