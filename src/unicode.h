/**(TAB=0)**********************************************************************
*
*  UNICODE.H   : Character Definitions
*
*  Author      : Ulf Dunkel (fd)
*  Co-Author(s): -
*  Write Access: fd
*    
* ------------------------------------------------------------------------------
*  Notes:
*
* ------------------------------------------------------------------------------
*
*  History:
*
*  2002:
*    fd  Aug 03: - file introduced
*                - 0000-007F: C0 Controls and Basic Latin
*                - 0080-00FF: C1 Controls and Latin-1 Supplement
*                - 0100-017F: Latin Extended-A
*                - 0180-024F: Latin Extended-B
*                - "Unicode to ANSI transforming codepages" introduced
*    fd  Aug 04: - Unicode range definitions completed in general, using the
*                  data provided at "http://www.unicode.org/charts/"
*    fd  Aug 05: 20A0-20CF (Currency Symbols) introduced
*    fd  Aug 06: - 2000-206F: General Punctuation
*                - 02B0-02FF: Spacing Modifier Letters
*                - 2100-214F: Letterlike Symbols
*    fd  Aug 13: - 2200-22FF: Mathematical Operators (some)
*                - 25A0-25FF: Geometric Shapes (some)
*    fd  Aug 14: - 2600-26FF: Miscellaneous Symbols
*                - 0300-036F: Combining Diacritical Marks
*    fd  Aug 19: - E000-F8FF: defining swap characters for CZE CFN fonts
*  2010:
*    fd  Jan 25: - 05D0-05EA: some Hebrew characters added for TOS
*                - various mathematical characters added (0x22..)
*                - 0370-03FF: Greek (incomplete, just the main alphabeth)
*    fd  Feb 15: - 25A0-25FF completed
*                - 2580-259F completed
*    fd  Feb 16: tiny adjustments
*    fd  Feb 19: 0400-04FF: Cyrillic
*    fd  Feb 22: - void, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*                - 0370-03ff completed (Greek)
*    fd  Feb 24: - 0590-05FF completed (Hebrew)
*                - 0600-06FF: Arabic
*    fd  Mar 05: typo fixed: U_LatinSmallLetterEng
*    fd  Mar 08: - 0E00-0E7F: Thai
*                - 1E00-1EFF: Latin Extended Additional
*
******************************************|************************************/
/*KEY _NAME="unicode definitions" */
/*END*/

#ifndef __UNICODE_H__
#define __UNICODE_H__

/*******************************************************************************
*
*     INCLUDE FILES
*
******************************************|************************************/
/*KEY _END */




/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/


   /* ====== Unicode to ANSI transforming codepages: ====== */

                                         /* -1: Not implemented yet */

#define U_ANSI_437UnitedStatesIBM    -1
#define U_ANSI_708Arabic             -1  /* (ASMO 708) */
#define U_ANSI_709Arabic             -1  /* (ASMO 449+, BCON V4) */
#define U_ANSI_710Arabic             -1  /* (transparent Arabic) */
#define U_ANSI_711Arabic             -1  /* (Nafitha Enhanced) */
#define U_ANSI_720Arabic             -1  /* (transparent ASMO) */
#define U_ANSI_819Windows            -1  /* Win3.1 (United States and Western Europe) */
#define U_ANSI_850IBM                -1  /* multilingual */
#define U_ANSI_852EasternEuropean    -1
#define U_ANSI_860Portuguese         -1
#define U_ANSI_862Hebrew             -1
#define U_ANSI_863FrenchCanadian     -1
#define U_ANSI_864Arabic             -1
#define U_ANSI_865Norwegian          -1
#define U_ANSI_866SovietUnion        -1
#define U_ANSI_874Thai               -1
#define U_ANSI_932Japanese           -1
#define U_ANSI_936SimplifiedChinese  -1
#define U_ANSI_949Korean             -1
#define U_ANSI_950TraditionalChinese -1
#define U_ANSI_1250Windows            1  /* Win3.1 (Eastern European) */
#define U_ANSI_1251Windows           -1  /* Win3.1 (Cyrillic) */
#define U_ANSI_1252WesternEuropean    0
#define U_ANSI_1253Greek             -1
#define U_ANSI_1254Turkish           -1
#define U_ANSI_1255Hebrew            -1
#define U_ANSI_1256Arabic            -1
#define U_ANSI_1257Baltic            -1
#define U_ANSI_1258Vietnamese        -1
#define U_ANSI_1361Johab             -1





   /* ====== Unicode Character Database: ====== */

   /* ------ C0 Controls and Basic Latin ------ */
   /* ------ Controls: */

#define U_NUL                                           0x0000  /* NULl */
#define U_SOH                                           0x0001  /* Start Of Heading */
#define U_STX                                           0x0002  /* Start of TeXt */
#define U_ETX                                           0x0003  /* End of TeXt */
#define U_EOT                                           0x0004  /* End Of Transmission */
#define U_ENQ                                           0x0005  /* ENQuiry */
#define U_ACK                                           0x0006  /* ACKnowledge */
#define U_BEL                                           0x0007  /* BELl */
#define U_BS                                            0x0008  /* BackSpace */
#define U_HT                                            0x0009  /* Horizontal Tabulation */
#define U_LF                                            0x000A  /* Line Feed */
#define U_VT                                            0x000B  /* Vertical Tabulation */
#define U_FF                                            0x000C  /* Form Feed */
#define U_CR                                            0x000D  /* Carriage Return */
#define U_SO                                            0x000E  /* Shift Out */
#define U_SI                                            0x000F  /* Shift In */
#define U_DLE                                           0x0010  /* Data Link Escape */
#define U_DC1                                           0x0011  /* Device Control 1 */
#define U_DC2                                           0x0012  /* Device Control 2 */
#define U_DC3                                           0x0013  /* Device Control 3 */
#define U_DC4                                           0x0014  /* Device Control 4 */
#define U_NAK                                           0x0015  /* Negative AcKnowledge */
#define U_SYN                                           0x0016  /* SYNchronous idle */
#define U_ETB                                           0x0017  /* End of Transmission Block */
#define U_CAN                                           0x0018  /* CANcel */
#define U_EM                                            0x0019  /* End of Medium */
#define U_SUB                                           0x001A  /* SUBstitute */
#define U_ESC                                           0x001B  /* ESCape */
#define U_FS                                            0x001C  /* File Separator */
#define U_GS                                            0x001D  /* Group Separator */
#define U_RS                                            0x001E  /* Record Separator */
#define U_US                                            0x001F  /* Unit Separator */

   /* ------ ASCII (Basic Latin): */

#define U_SP                                            0x0020  /* SPace */
#define U_ExclamationMark                               0x0021  /* ! */
#define U_QuotationMark                                 0x0022  /* " */
#define U_NumberSign                                    0x0023  /* # */
#define U_DollarSign                                    0x0024  /* $ */
#define U_PercentSign                                   0x0025  /* % */
#define U_Ampersand                                     0x0026  /* & */
#define U_Apostrophe                                    0x0027  /* ' */
#define U_OpeningParenthesis                            0x0028  /* ( */
#define U_ClosingParenthesis                            0x0029  /* ) */
#define U_Asterisk                                      0x002A  /* * */
#define U_PlusSign                                      0x002B  /* + */
#define U_Comma                                         0x002C  /* , */
#define U_HyphenMinus                                   0x002D  /* - */
#define U_Period                                        0x002E  /* . */
#define U_Slash                                         0x002F  /* / */
#define U_Digit0                                        0x0030  /* 0 */
#define U_Digit1                                        0x0031  /* 1 */
#define U_Digit2                                        0x0032  /* 2 */
#define U_Digit3                                        0x0033  /* 3 */
#define U_Digit4                                        0x0034  /* 4 */
#define U_Digit5                                        0x0035  /* 5 */
#define U_Digit6                                        0x0036  /* 6 */
#define U_Digit7                                        0x0037  /* 7 */
#define U_Digit8                                        0x0038  /* 8 */
#define U_Digit9                                        0x0039  /* 9 */
#define U_Colon                                         0x003A  /* : */
#define U_Semicolon                                     0x003B  /* ; */
#define U_LessThanSign                                  0x003C  /* < */
#define U_EqualsSign                                    0x003D  /* = */
#define U_GreaterThanSign                               0x003E  /* > */
#define U_QuestionMark                                  0x003F  /* ? */
#define U_CommercialAt                                  0x0040  /* @ */
#define U_LatinCapitalLetterA                           0x0041  /* A */
#define U_LatinCapitalLetterB                           0x0042  /* B */
#define U_LatinCapitalLetterC                           0x0043  /* C */
#define U_LatinCapitalLetterD                           0x0044  /* D */
#define U_LatinCapitalLetterE                           0x0045  /* E */
#define U_LatinCapitalLetterF                           0x0046  /* F */
#define U_LatinCapitalLetterG                           0x0047  /* G */
#define U_LatinCapitalLetterH                           0x0048  /* H */
#define U_LatinCapitalLetterI                           0x0049  /* I */
#define U_LatinCapitalLetterJ                           0x004A  /* J */
#define U_LatinCapitalLetterK                           0x004B  /* K */
#define U_LatinCapitalLetterL                           0x004C  /* L */
#define U_LatinCapitalLetterM                           0x004D  /* M */
#define U_LatinCapitalLetterN                           0x004E  /* N */
#define U_LatinCapitalLetterO                           0x004F  /* O */
#define U_LatinCapitalLetterP                           0x0050  /* P */
#define U_LatinCapitalLetterQ                           0x0051  /* Q */
#define U_LatinCapitalLetterR                           0x0052  /* R */
#define U_LatinCapitalLetterS                           0x0053  /* S */
#define U_LatinCapitalLetterT                           0x0054  /* T */
#define U_LatinCapitalLetterU                           0x0055  /* U */
#define U_LatinCapitalLetterV                           0x0056  /* V */
#define U_LatinCapitalLetterW                           0x0057  /* W */
#define U_LatinCapitalLetterX                           0x0058  /* X */
#define U_LatinCapitalLetterY                           0x0059  /* Y */
#define U_LatinCapitalLetterZ                           0x005A  /* Z */
#define U_OpeningSquareBracket                          0x005B  /* [ */
#define U_Backslash                                     0x005C  /* \ */
#define U_ClosingSquareBracket                          0x005D  /* ] */
#define U_CircumflexAccent                              0x005E  /* ^ */
#define U_SpacingUnderscore                             0x005F  /* _ */
#define U_GraveAccent                                   0x0060  /* ` */
#define U_LatinSmallLetterA                             0x0061  /* a */
#define U_LatinSmallLetterB                             0x0062  /* b */
#define U_LatinSmallLetterC                             0x0063  /* c */
#define U_LatinSmallLetterD                             0x0064  /* d */
#define U_LatinSmallLetterE                             0x0065  /* e */
#define U_LatinSmallLetterF                             0x0066  /* f */
#define U_LatinSmallLetterG                             0x0067  /* g */
#define U_LatinSmallLetterH                             0x0068  /* h */
#define U_LatinSmallLetterI                             0x0069  /* i */
#define U_LatinSmallLetterJ                             0x006A  /* j */
#define U_LatinSmallLetterK                             0x006B  /* k */
#define U_LatinSmallLetterL                             0x006C  /* l */
#define U_LatinSmallLetterM                             0x006D  /* m */
#define U_LatinSmallLetterN                             0x006E  /* n */
#define U_LatinSmallLetterO                             0x006F  /* o */
#define U_LatinSmallLetterP                             0x0070  /* p */
#define U_LatinSmallLetterQ                             0x0071  /* q */
#define U_LatinSmallLetterR                             0x0072  /* r */
#define U_LatinSmallLetterS                             0x0073  /* s */
#define U_LatinSmallLetterT                             0x0074  /* t */
#define U_LatinSmallLetterU                             0x0075  /* u */
#define U_LatinSmallLetterV                             0x0076  /* v */
#define U_LatinSmallLetterW                             0x0077  /* w */
#define U_LatinSmallLetterX                             0x0078  /* x */
#define U_LatinSmallLetterY                             0x0079  /* y */
#define U_LatinSmallLetterZ                             0x007A  /* z */
#define U_OpeningCurlyBracket                           0x007B  /* { */
#define U_VerticalLine                                  0x007C  /* | */
#define U_ClosingCurlyBracket                           0x007D  /* } */
#define U_Tilde                                         0x007E  /* ~ */
#define U_DEL                                           0x007F  /* Delete */


   /* ------ C1 Controls and Latin-1 Supplement ------ */
   /* ------ Controls: */

#define U_XXX_0080                                      0x0080  /* control */
#define U_XXX_0081                                      0x0081  /* control */
#define U_BPH                                           0x0082  /* Break Permitted Here */
#define U_NBH                                           0x0083  /* No Break Here */
#define U_XXX_0084                                      0x0084  /* control */
#define U_NEL                                           0x0085  /* NExt Line */
#define U_SSA                                           0x0086  /* Start of Selected Area */
#define U_ESA                                           0x0087  /* End of Selected Area */
#define U_HTS                                           0x0088  /* cHaracter Tabulation Set */
#define U_HTJ                                           0x0089  /* cHaracter Tabulation With Justification */
#define U_VTS                                           0x008A  /* line Tabulation Set */
#define U_PLD                                           0x008B  /* Partial Line Down */
#define U_PLU                                           0x008C  /* Partial Line Up */
#define U_RI                                            0x008D  /* Reverse lIne Feed */
#define U_SS2                                           0x008E  /* Single Shift 2 */
#define U_SS3                                           0x008F  /* Single Shift 3 */
#define U_DCS                                           0x0090  /* Device Control String */
#define U_PU1                                           0x0091  /* Private Use 1 */
#define U_PU2                                           0x0092  /* Private Use 2 */
#define U_STS                                           0x0093  /* Set Transmit State */
#define U_CCH                                           0x0094  /* Cancel CHaracter */
#define U_MW                                            0x0095  /* Message Waiting */
#define U_SPA                                           0x0096  /* Start of guarded Area */
#define U_EPA                                           0x0097  /* End of guarded Area */
#define U_SOS                                           0x0098  /* Start Of String */
#define U_XXX_0099                                      0x0099  /* control */
#define U_SCI                                           0x009A  /* Single Character Introducer */
#define U_CSI                                           0x009B  /* Control Sequence Introducer */
#define U_ST                                            0x009C  /* String Terminator */
#define U_OSC                                           0x009D  /* Operating System Command */
#define U_PM                                            0x009E  /* Privacy Message */
#define U_APC                                           0x009F  /* Application Program Command */

   /* ------ ISO 8859-1 (aka Latin-1): */

#define U_NB_SP                                         0x00A0  /* No-Break SPace */
#define U_InvertedExclamationMark                       0x00A1  /*  */
#define U_CentSign                                      0x00A2  /* õ */
#define U_PoundSign                                     0x00A3  /* ú */
#define U_CurrencySign                                  0x00A4  /*  */
#define U_YenSign                                       0x00A5  /* ù */
#define U_BrokenVerticalBar                             0x00A6  /*  */
#define U_SectionSign                                   0x00A7  /*  */
#define U_Diaeresis                                     0x00A8  /*  */
#define U_CopyrightSign                                 0x00A9  /*  */
#define U_FeminineOrdinalIndicator                      0x00AA  /* ¶ */
#define U_LeftPointingGuillemet                         0x00AB  /*  */
#define U_NotSign                                       0x00AC  /*  */
#define U_SoftHyphen                                    0x00AD  /*  */
#define U_RegisteredSign                                0x00AE  /*  */
#define U_Macron                                        0x00AF  /*  */
#define U_DegreeSign                                    0x00B0  /*  */
#define U_PlusMinusSign                                 0x00B1  /*  */
#define U_SuperscriptTwo                                0x00B2  /*  */
#define U_SuperscriptThree                              0x00B3  /*  */
#define U_AcuteAccent                                   0x00B4  /*  */
#define U_MicroSign                                     0x00B5  /*  */
#define U_ParagraphSign                                 0x00B6  /*  */
#define U_MiddleDot                                     0x00B7  /*  */
#define U_Cedilla                                       0x00B8  /*  */
#define U_SuperscriptOne                                0x00B9  /*  */
#define U_MasculineOrdinalIndicator                     0x00BA  /* ß */
#define U_RightPointingGuillemet                        0x00BB  /*  */
#define U_VulgarFractionOneQuarter                      0x00BC  /*  */
#define U_VulgarFractionOneHalf                         0x00BD  /*  */
#define U_VulgarFractionThreeQuarters                   0x00BE  /*  */
#define U_InvertedQuestionMark                          0x00BF  /*  */
#define U_LatinCapitalLetterAWithGrave                  0x00C0  /*  */
#define U_LatinCapitalLetterAWithAcute                  0x00C1  /*  */
#define U_LatinCapitalLetterAWithCircumflex             0x00C2  /*  */
#define U_LatinCapitalLetterAWithTilde                  0x00C3  /*  */
#define U_LatinCapitalLetterAWithDiaeresis              0x00C4  /* é */
#define U_LatinCapitalLetterAWithRingAbove              0x00C5  /* è */
#define U_LatinCapitalLigatureAE                        0x00C6  /* í */
#define U_LatinCapitalLetterCWithCedilla                0x00C7  /* Ä */
#define U_LatinCapitalLetterEWithGrave                  0x00C8  /*  */
#define U_LatinCapitalLetterEWithAcute                  0x00C9  /* ê */
#define U_LatinCapitalLetterEWithCircumflex             0x00CA  /*  */
#define U_LatinCapitalLetterEWithDiaeresis              0x00CB  /*  */
#define U_LatinCapitalLetterIWithGrave                  0x00CC  /*  */
#define U_LatinCapitalLetterIWithAcute                  0x00CD  /*  */
#define U_LatinCapitalLetterIWithCircumflex             0x00CE  /*  */
#define U_LatinCapitalLetterIWithDiaeresis              0x00CF  /*  */
#define U_LatinCapitalLetterEth                         0x00D0  /*  */
#define U_LatinCapitalLetterNWithTilde                  0x00D1  /* • */
#define U_LatinCapitalLetterOWithGrave                  0x00D2  /*  */
#define U_LatinCapitalLetterOWithAcute                  0x00D3  /*  */
#define U_LatinCapitalLetterOWithCircumflex             0x00D4  /*  */
#define U_LatinCapitalLetterOWithTilde                  0x00D5  /*  */
#define U_LatinCapitalLetterOWithDiaeresis              0x00D6  /* ô */
#define U_MultiplicationSign                            0x00D7  /*  */
#define U_LatinCapitalLetterOSlash                      0x00D8  /*  */
#define U_LatinCapitalLetterUWithGrave                  0x00D9  /*  */
#define U_LatinCapitalLetterUWithAcute                  0x00DA  /*  */
#define U_LatinCapitalLetterUWithCircumflex             0x00DB  /*  */
#define U_LatinCapitalLetterUWithDiaeresis              0x00DC  /* ö */
#define U_LatinCapitalLetterYWithAcute                  0x00DD  /*  */
#define U_LatinCapitalLetterThorn                       0x00DE  /*  */
#define U_LatinSmallLetterSharpS                        0x00DF  /*  */
#define U_LatinSmallLetterAWithGrave                    0x00E0  /* Ö */
#define U_LatinSmallLetterAWithAcute                    0x00E1  /* † */
#define U_LatinSmallLetterAWithCircumflex               0x00E2  /* É */
#define U_LatinSmallLetterAWithTilde                    0x00E3  /*  */
#define U_LatinSmallLetterAWithDiaeresis                0x00E4  /* Ñ */
#define U_LatinSmallLetterAWithRingAbove                0x00E5  /* Ü */
#define U_LatinSmallLigatureAE                          0x00E6  /* ë */
#define U_LatinSmallLetterCWithCedilla                  0x00E7  /* á */
#define U_LatinSmallLetterEWithGrave                    0x00E8  /* ä */
#define U_LatinSmallLetterEWithAcute                    0x00E9  /* Ç */
#define U_LatinSmallLetterEWithCircumflex               0x00EA  /* à */
#define U_LatinSmallLetterEWithDiaeresis                0x00EB  /* â */
#define U_LatinSmallLetterIWithGrave                    0x00EC  /* ç */
#define U_LatinSmallLetterIWithAcute                    0x00ED  /* ° */
#define U_LatinSmallLetterIWithCircumflex               0x00EE  /* å */
#define U_LatinSmallLetterIWithDiaeresis                0x00EF  /* ã */
#define U_LatinSmallLetterEth                           0x00F0  /*  */
#define U_LatinSmallLetterNWithTilde                    0x00F1  /* § */
#define U_LatinSmallLetterOWithGrave                    0x00F2  /* ï */
#define U_LatinSmallLetterOWithAcute                    0x00F3  /* ¢ */
#define U_LatinSmallLetterOWithCircumflex               0x00F4  /* ì */
#define U_LatinSmallLetterOWithTilde                    0x00F5  /*  */
#define U_LatinSmallLetterOWithDiaeresis                0x00F6  /* î */
#define U_DivisionSign                                  0x00F7  /*  */
#define U_LatinSmallLetterOSlash                        0x00F8  /*  */
#define U_LatinSmallLetterUWithGrave                    0x00F9  /* ó */
#define U_LatinSmallLetterUWithAcute                    0x00FA  /* £ */
#define U_LatinSmallLetterUWithCircumflex               0x00FB  /* ñ */
#define U_LatinSmallLetterUWithDiaeresis                0x00FC  /* Å */
#define U_LatinSmallLetterYWithAcute                    0x00FD  /*  */
#define U_LatinSmallLetterThorn                         0x00FE  /*  */
#define U_LatinSmallLetterYWithDiaeresis                0x00FF  /* ò */


   /* ------ Latin Extended-A: ------ */

#define U_LatinCapitalLetterAWithMacron                 0x0100  /*  */
#define U_LatinSmallLetterAWithMacron                   0x0101  /*  */
#define U_LatinCapitalLetterAWithBreve                  0x0102  /*  */
#define U_LatinSmallLetterAWithBreve                    0x0103  /*  */
#define U_LatinCapitalLetterAWithOgonek                 0x0104  /*  */
#define U_LatinSmallLetterAWithOgonek                   0x0105  /*  */
#define U_LatinCapitalLetterCWithAcute                  0x0106  /*  */
#define U_LatinSmallLetterCWithAcute                    0x0107  /*  */
#define U_LatinCapitalLetterCWithCircumflex             0x0108  /*  */
#define U_LatinSmallLetterCWithCircumflex               0x0109  /*  */
#define U_LatinCapitalLetterCWithDotAbove               0x010A  /*  */
#define U_LatinSmallLetterCWithDotAbove                 0x010B  /*  */
#define U_LatinCapitalLetterCWithCaron                  0x010C  /*  */
#define U_LatinSmallLetterCWithCaron                    0x010D  /*  */
#define U_LatinCapitalLetterDWithCaron                  0x010E  /*  */
#define U_LatinSmallLetterDWithCaron                    0x010F  /*  */
#define U_LatinCapitalLetterDWithStroke                 0x0110  /*  */
#define U_LatinSmallLetterDWithStroke                   0x0111  /*  */
#define U_LatinCapitalLetterEWithMacron                 0x0112  /*  */
#define U_LatinSmallLetterEWithMacron                   0x0113  /*  */
#define U_LatinCapitalLetterEWithBreve                  0x0114  /*  */
#define U_LatinSmallLetterEWithBreve                    0x0115  /*  */
#define U_LatinCapitalLetterEWithDotAbove               0x0116  /*  */
#define U_LatinSmallLetterEWithDotAbove                 0x0117  /*  */
#define U_LatinCapitalLetterEWithOgonek                 0x0118  /*  */
#define U_LatinSmallLetterEWithOgonek                   0x0119  /*  */
#define U_LatinCapitalLetterEWithCaron                  0x011A  /*  */
#define U_LatinSmallLetterEWithCaron                    0x011B  /*  */
#define U_LatinCapitalLetterGWithCircumflex             0x011C  /*  */
#define U_LatinSmallLetterGWithCircumflex               0x011D  /*  */
#define U_LatinCapitalLetterGWithBreve                  0x011E  /*  */
#define U_LatinSmallLetterGWithBreve                    0x011F  /*  */
#define U_LatinCapitalLetterGWithDotAbove               0x0120  /*  */
#define U_LatinSmallLetterGWithDotAbove                 0x0121  /*  */
#define U_LatinCapitalLetterGWithCedilla                0x0122  /*  */
#define U_LatinSmallLetterGWithCedilla                  0x0123  /*  */
#define U_LatinCapitalLetterHWithCircumflex             0x0124  /*  */
#define U_LatinSmallLetterHWithCircumflex               0x0125  /*  */
#define U_LatinCapitalLetterHWithStroke                 0x0126  /*  */
#define U_LatinSmallLetterHWithStroke                   0x0127  /*  */
#define U_LatinCapitalLetterIWithTilde                  0x0128  /*  */
#define U_LatinSmallLetterIWithTilde                    0x0129  /*  */
#define U_LatinCapitalLetterIWithMacron                 0x012A  /*  */
#define U_LatinSmallLetterIWithMacron                   0x012B  /*  */
#define U_LatinCapitalLetterIWithBreve                  0x012C  /*  */
#define U_LatinSmallLetterIWithBreve                    0x012D  /*  */
#define U_LatinCapitalLetterIWithOgonek                 0x012E  /*  */
#define U_LatinSmallLetterIWithOgonek                   0x012F  /*  */
#define U_LatinCapitalLetterIWithDotAbove               0x0130  /*  */
#define U_LatinSmallLetterDotlessI                      0x0131  /*  */
#define U_LatinCapitalLigatureIJ                        0x0132  /*  */
#define U_LatinSmallLigatureIJ                          0x0133  /*  */
#define U_LatinCapitalLetterJWithCircumflex             0x0134  /*  */
#define U_LatinSmallLetterJWithCircumflex               0x0135  /*  */
#define U_LatinCapitalLetterKWithCedilla                0x0136  /*  */
#define U_LatinSmallLetterKWithCedilla                  0x0137  /*  */
#define U_LatinSmallLetterKra                           0x0138  /*  */
#define U_LatinCapitalLetterLWithAcute                  0x0139  /*  */
#define U_LatinSmallLetterLWithAcute                    0x013A  /*  */
#define U_LatinCapitalLetterLWithCedilla                0x013B  /*  */
#define U_LatinSmallLetterLWithCedilla                  0x013C  /*  */
#define U_LatinCapitalLetterLWithCaron                  0x013D  /*  */
#define U_LatinSmallLetterLWithCaron                    0x013E  /*  */
#define U_LatinCapitalLetterLWithMiddleDot              0x013F  /*  */
#define U_LatinSmallLetterLWithMiddleDot                0x0140  /*  */
#define U_LatinCapitalLetterLWithStroke                 0x0141  /*  */
#define U_LatinSmallLetterLWithStroke                   0x0142  /*  */
#define U_LatinCapitalLetterNWithAcute                  0x0143  /*  */
#define U_LatinSmallLetterNWithAcute                    0x0144  /*  */
#define U_LatinCapitalLetterNWithCedilla                0x0145  /*  */
#define U_LatinSmallLetterNWithCedilla                  0x0146  /*  */
#define U_LatinCapitalLetterNWithCaron                  0x0147  /*  */
#define U_LatinSmallLetterNWithCaron                    0x0148  /*  */
#define U_LatinSmallLetterApostropheN                   0x0149  /*  */
#define U_LatinCapitalLetterEng                         0x014A  /*  */
#define U_LatinSmallLetterEng                           0x014B  /*  */
#define U_LatinCapitalLetterOWithMacron                 0x014C  /*  */
#define U_LatinSmallLetterOWithMacron                   0x014D  /*  */
#define U_LatinCapitalLetterOWithBreve                  0x014E  /*  */
#define U_LatinSmallLetterOWithBreve                    0x014F  /*  */
#define U_LatinCapitalLetterOWithDoubleAcute            0x0150  /*  */
#define U_LatinSmallLetterOWithDoubleAcute              0x0151  /*  */
#define U_LatinCapitalLigatureOE                        0x0152  /*  */
#define U_LatinSmallLigatureOE                          0x0153  /*  */
#define U_LatinCapitalLetterRWithAcute                  0x0154  /*  */
#define U_LatinSmallLetterRWithAcute                    0x0155  /*  */
#define U_LatinCapitalLetterRWithCedilla                0x0156  /*  */
#define U_LatinSmallLetterRWithCedilla                  0x0157  /*  */
#define U_LatinCapitalLetterRWithCaron                  0x0158  /*  */
#define U_LatinSmallLetterRWithCaron                    0x0159  /*  */
#define U_LatinCapitalLetterSWithAcute                  0x015A  /*  */
#define U_LatinSmallLetterSWithAcute                    0x015B  /*  */
#define U_LatinCapitalLetterSWithCircumflex             0x015C  /*  */
#define U_LatinSmallLetterSWithCircumflex               0x015D  /*  */
#define U_LatinCapitalLetterSWithCedilla                0x015E  /*  */
#define U_LatinSmallLetterSWithCedilla                  0x015F  /*  */
#define U_LatinCapitalLetterSWithCaron                  0x0160  /*  */
#define U_LatinSmallLetterSWithCaron                    0x0161  /*  */
#define U_LatinCapitalLetterTWithCedilla                0x0162  /*  */
#define U_LatinSmallLetterTWithCedilla                  0x0163  /*  */
#define U_LatinCapitalLetterTWithCaron                  0x0164  /*  */
#define U_LatinSmallLetterTWithCaron                    0x0165  /*  */
#define U_LatinCapitalLetterTWithStroke                 0x0166  /*  */
#define U_LatinSmallLetterTWithStroke                   0x0167  /*  */
#define U_LatinCapitalLetterUWithTilde                  0x0168  /*  */
#define U_LatinSmallLetterUWithTilde                    0x0169  /*  */
#define U_LatinCapitalLetterUWithMacron                 0x016A  /*  */
#define U_LatinSmallLetterUWithMacron                   0x016B  /*  */
#define U_LatinCapitalLetterUWithBreve                  0x016C  /*  */
#define U_LatinSmallLetterUWithBreve                    0x016D  /*  */
#define U_LatinCapitalLetterUWithRingAbove              0x016E  /*  */
#define U_LatinSmallLetterUWithRingAbove                0x016F  /*  */
#define U_LatinCapitalLetterUWithDoubleAcute            0x0170  /*  */
#define U_LatinSmallLetterUWithDoubleAcute              0x0171  /*  */
#define U_LatinCapitalLetterUWithOgonek                 0x0172  /*  */
#define U_LatinSmallLetterUWithOgonek                   0x0173  /*  */
#define U_LatinCapitalLetterWWithCircumflex             0x0174  /*  */
#define U_LatinSmallLetterWWithCircumflex               0x0175  /*  */
#define U_LatinCapitalLetterYWithCircumflex             0x0176  /*  */
#define U_LatinSmallLetterYWithCircumflex               0x0177  /*  */
#define U_LatinCapitalLetterYWithDiaeresis              0x0178  /*  */
#define U_LatinCapitalLetterZWithAcute                  0x0179  /*  */
#define U_LatinSmallLetterZWithAcute                    0x017A  /*  */
#define U_LatinCapitalLetterZWithDotAbove               0x017B  /*  */
#define U_LatinSmallLetterZWithDotAbove                 0x017C  /*  */
#define U_LatinCapitalLetterZWithCaron                  0x017D  /*  */
#define U_LatinSmallLetterZWithCaron                    0x017E  /*  */
#define U_LatinSmallLetterLongS                         0x017F  /*  */


   /* ------ Latin Extended-B: ------ */
   /* ------ Latin Extended-B: ------ */

#define U_LatinSmallLetterBWithStroke                   0x0180  /*  */
#define U_LatinCapitalLetterBWithHook                   0x0181  /*  */
#define U_LatinCapitalLetterBWithTopbar                 0x0182  /*  */
#define U_LatinSmallLetterBWithTopbar                   0x0183  /*  */
#define U_LatinCapitalLetterToneSix                     0x0184  /*  */
#define U_LatinSmallLetterToneSix                       0x0185  /*  */
#define U_LatinCapitalLetterOpenO                       0x0186  /*  */
#define U_LatinCapitalLetterCWithHook                   0x0187  /*  */
#define U_LatinSmallLetterCWithHook                     0x0188  /*  */
#define U_LatinCapitalLetterAfricanD                    0x0189  /*  */
#define U_LatinCapitalLetterDWithHook                   0x018A  /*  */
#define U_LatinCapitalLetterDWithTopbar                 0x018B  /*  */
#define U_LatinSmallLetterDWithTopbar                   0x018C  /*  */
#define U_LatinSmallLetterTurnedDelta                   0x018D  /*  */
#define U_LatinCapitalLetterReversedE                   0x018E  /*  */
#define U_LatinCapitalLetterSchwa                       0x018F  /*  */
#define U_LatinCapitalLetterEpsilon                     0x0190  /*  */
#define U_LatinCapitalLetterFWithHook                   0x0191  /*  */
#define U_LatinSmallLetterScriptF                       0x0192  /* LATIN SMALL LETTER F WITH HOOK, florijn */
#define U_LatinCapitalLetterGWithHook                   0x0193  /*  */
#define U_LatinCapitalLetterGamma                       0x0194  /*  */
#define U_LatinSmallLetterHV                            0x0195  /*  */
#define U_LatinCapitalLetterIota                        0x0196  /*  */
#define U_LatinCapitalLetterIWithStroke                 0x0197  /*  */
#define U_LatinCapitalLetterKWithHook                   0x0198  /*  */
#define U_LatinSmallLetterKWithHook                     0x0199  /*  */
#define U_LatinSmallLetterLWithBar                      0x019A  /*  */
#define U_LatinSmallLetterLambdaWithStroke              0x019B  /*  */
#define U_LatinCapitalLetterTurnedM                     0x019C  /*  */
#define U_LatinCapitalLetterNWithLeftHook               0x019D  /*  */
#define U_LatinSmallLetterNWithLongRightLeg             0x019E  /*  */
#define U_LatinCapitalLetterOWithMiddleTilde            0x019F  /*  */
#define U_LatinCapitalLetterOWithHorn                   0x01A0  /*  */
#define U_LatinSmallLetterOWithHorn                     0x01A1  /*  */
#define U_LatinCapitalLetterOI                          0x01A2  /*  */
#define U_LatinSmallLetterOI                            0x01A3  /*  */
#define U_LatinCapitalLetterPWithHook                   0x01A4  /*  */
#define U_LatinSmallLetterPWithHook                     0x01A5  /*  */
#define U_LatinLetterYR                                 0x01A6  /*  */
#define U_LatinCapitalLetterToneTwo                     0x01A7  /*  */
#define U_LatinSmallLetterToneTwo                       0x01A8  /*  */
#define U_LatinCapitalLetterEsh                         0x01A9  /*  */
#define U_LatinLetterReversedEshLoop                    0x01AA  /*  */
#define U_LatinSmallLetterTWithPalatalHook              0x01AB  /*  */
#define U_LatinCapitalLetterTWithHook                   0x01AC  /*  */
#define U_LatinSmallLetterTWithHook                     0x01AD  /*  */
#define U_LatinCapitalLetterTWithRetroflexHook          0x01AE  /*  */
#define U_LatinCapitalLetterUWithHorn                   0x01AF  /*  */
#define U_LatinSmallLetterUWithHorn                     0x01B0  /*  */
#define U_LatinCapitalLetterUpsilon                     0x01B1  /*  */
#define U_LatinCapitalLetterScriptV                     0x01B2  /*  */
#define U_LatinCapitalLetterYWithHook                   0x01B3  /*  */
#define U_LatinSmallLetterYWithHook                     0x01B4  /*  */
#define U_LatinCapitalLetterZWithStroke                 0x01B5  /*  */
#define U_LatinSmallLetterZWithStroke                   0x01B6  /*  */
#define U_LatinCapitalLEtterEzh                         0x01B7  /*  */
#define U_LatinCapitalLetterEzhReversed                 0x01B8  /*  */
#define U_LatinSmallLetterEzhReversed                   0x01B9  /*  */
#define U_LatinSmallLetterEzhWithTail                   0x01BA  /*  */
#define U_LatinLetterTwoWithStroke                      0x01BB  /*  */
#define U_LatinCapitalLetterToneFive                    0x01BC  /*  */
#define U_LatinSmallLetterToneFive                      0x01BD  /*  */
#define U_LatinLetterInvertedGlottalStopWithStroke      0x01BE  /*  */
#define U_LatinLetterWynn                               0x01BF  /*  */
#define U_LatinLetterDentalClick                        0x01C0  /*  */
#define U_LatinLetterLateralClick                       0x01C1  /*  */
#define U_LatinLetterAlveolarClick                      0x01C2  /*  */
#define U_LatinLetterRetroflexClick                     0x01C3  /*  */

   /* ------ Croatian digraphs matching Serbian Cyrillic Letters: ------ */

#define U_LatinCapitalLetterDZWithCaron                 0x01C4  /*  */
#define U_LatinCapitalLetterDWithSmallLetterZWithCaron  0x01C5  /*  */
#define U_LatinSmallLetterDZWithCaron                   0x01C6  /*  */
#define U_LatinCapitalLetterLJ                          0x01C7  /*  */
#define U_LatinCapitalLetterLWithSmallLetterJ           0x01C8  /*  */
#define U_LatinSmallLetterLJ                            0x01C9  /*  */
#define U_LatinCapitalLetterNJ                          0x01CA  /*  */
#define U_LatinCapitalLetterNWithSmallLetterJ           0x01CB  /*  */
#define U_LatinSmallLetterNJ                            0x01CC  /*  */

   /* ------ Pinyin diacritic-vowel combinations: ------ */

#define U_LatinCapitalLetterAWithCaron                  0x01CD  /*  */
#define U_LatinSmallLetterAWithCaron                    0x01CE  /*  */
#define U_LatinCapitalLetterIWithCaron                  0x01CF  /*  */
#define U_LatinSmallLetterIWithCaron                    0x01D0  /*  */
#define U_LatinCapitalLetterOWithCaron                  0x01D1  /*  */
#define U_LatinSmallLetterOWithCaron                    0x01D2  /*  */
#define U_LatinCapitalLetterUWithCaron                  0x01D3  /*  */
#define U_LatinSmallLetterUWithCaron                    0x01D4  /*  */
#define U_LatinCapitalLetterUWithDiaeresisAndMacron     0x01D5  /*  */
#define U_LatinSmallLetterUWithDiaeresisAndMacron       0x01D6  /*  */
#define U_LatinCapitalLetterUWithDiaeresisAndAcute      0x01D7  /*  */
#define U_LatinSmallLetterUWithDiaeresisAndAcute        0x01D8  /*  */
#define U_LatinCapitalLetterUWithDiaeresisAndCaron      0x01D9  /*  */
#define U_LatinSmallLetterUWithDiaeresisAndCaron        0x01DA  /*  */
#define U_LatinCapitalLetterUWithDiaeresisAndGrave      0x01DB  /*  */
#define U_LatinSmallLetterUWithDiaeresisAndGrave        0x01DC  /*  */

   /* ------ Additions: ------ */

#define U_LatinSmallLetterTurnedE                       0x01DD  /*  */
#define U_LatinCapitalLetterAWithDiaeresisAndMacron     0x01DE  /*  */
#define U_LatinSmallLetterAWithDiaeresisAndMacron       0x01DF  /*  */
#define U_LatinCapitalLetterAWithDotAboveAndMacron      0x01E0  /*  */
#define U_LatinSmallLetterAWithDotAboveAndMacron        0x01E1  /*  */
#define U_LatinCapitalLetterAEWithMacron                0x01E2  /*  */
#define U_LatinSmallLetterAEWithMacron                  0x01E3  /*  */
#define U_LatinCapitalLetterGWithStroke                 0x01E4  /*  */
#define U_LatinSmallLetterGWithStroke                   0x01E5  /*  */
#define U_LatinCapitalLetterGWithCaron                  0x01E6  /*  */
#define U_LatinSmallLetterGWithCaron                    0x01E7  /*  */
#define U_LatinCapitalLetterKWithCaron                  0x01E8  /*  */
#define U_LatinSmallLetterKWithCaron                    0x01E9  /*  */
#define U_LatinCapitalLetterOWithOgonek                 0x01EA  /*  */
#define U_LatinSmallLetterOWithOgonek                   0x01EB  /*  */
#define U_LatinCapitalLetterOWithOgonekAndMacron        0x01EC  /*  */
#define U_LatinSmallLetterOWithOgonekAndMacron          0x01ED  /*  */
#define U_LatinCapitalLetterEzhWithCaron                0x01EE  /*  */
#define U_LatinSmallLetterEzhWithCaron                  0x01EF  /*  */
#define U_LatinSmallLetterJWithCaron                    0x01F0  /*  */
#define U_LatinCapitalLetterDZ                          0x01F1  /*  */
#define U_LatinCapitalLetterDWithSmallLetterZ           0x01F2  /*  */
#define U_LatinSmallLetterDZ                            0x01F3  /*  */
#define U_LatinCapitalLetterGWithAcute                  0x01F4  /*  */
#define U_LatinSmallLetterGWithAcute                    0x01F5  /*  */
#define U_LatinCapitalLetterHwair                       0x01F6  /*  */
#define U_LatinCapitalLetterWynn                        0x01F7  /*  */
#define U_LatinCapitalLetterNWithGrave                  0x01F8  /*  */
#define U_LatinSmallLetterNWithGrave                    0x01F9  /*  */
#define U_LatinCapitalLetterAWithRingAboveAndAcute      0x01FA  /*  */
#define U_LatinSmallLetterAWithRingAboveAndAcute        0x01FB  /*  */
#define U_LatinCapitalLetterAEWithAcute                 0x01FC  /*  */
#define U_LatinSmallLetterAEWithAcute                   0x01FD  /*  */
#define U_LatinCapitalLetterOWithStrokeAndAcute         0x01FE  /*  */
#define U_LatinSmallLetterOWithStrokeAndAcute           0x01FF  /*  */

   /* ------ Additions for Slovenian and Croatian: ------ */

#define U_LatinCapitalLetterAWithDoubleGrave            0x0200  /*  */
#define U_LatinSmallLetterAWithDoubleGrave              0x0201  /*  */
#define U_LatinCapitalLetterAWithInvertedBreve          0x0202  /*  */
#define U_LatinSmallLetterAWithInvertedBreve            0x0203  /*  */
#define U_LatinCapitalLetterEWithDoubleGrave            0x0204  /*  */
#define U_LatinSmallLetterEWithDoubleGrave              0x0205  /*  */
#define U_LatinCapitalLetterEWithInvertedBreve          0x0206  /*  */
#define U_LatinSmallLetterEWithInvertedBreve            0x0207  /*  */
#define U_LatinCapitalLetterIWithDoubleGrave            0x0208  /*  */
#define U_LatinSmallLetterIWithDoubleGrave              0x0209  /*  */
#define U_LatinCapitalLetterIWithInvertedBreve          0x020A  /*  */
#define U_LatinSmallLetterIWithInvertedBreve            0x020B  /*  */
#define U_LatinCapitalLetterOWithDoubleGrave            0x020C  /*  */
#define U_LatinSmallLetterOWithDoubleGrave              0x020D  /*  */
#define U_LatinCapitalLetterOWithInvertedBreve          0x020E  /*  */
#define U_LatinSmallLetterOWithInvertedBreve            0x020F  /*  */
#define U_LatinCapitalLetterRWithDoubleGrave            0x0210  /*  */
#define U_LatinSmallLetterRWithDoubleGrave              0x0211  /*  */
#define U_LatinCapitalLetterRWithInvertedBreve          0x0212  /*  */
#define U_LatinSmallLetterRWithInvertedBreve            0x0213  /*  */
#define U_LatinCapitalLetterUWithDoubleGrave            0x0214  /*  */
#define U_LatinSmallLetterUWithDoubleGrave              0x0215  /*  */
#define U_LatinCapitalLetterUWithInvertedBreve          0x0216  /*  */
#define U_LatinSmallLetterUWithInvertedBreve            0x0217  /*  */

   /* ------ Additions for Romanian: ------ */

#define U_LatinCapitalLetterSWithCommaBelow             0x0218  /*  */
#define U_LatinSmallLetterSWithCommaBelow               0x0219  /*  */
#define U_LatinCapitalLetterTWithCommaBelow             0x021A  /*  */
#define U_LatinSmallLetterTWithCommaBelow               0x021B  /*  */

   /* ------ Miscellaneous additions: ------ */

#define U_LatinCapitalLetterYogh                        0x021C  /*  */
#define U_LatinSmallLetterYogh                          0x021D  /*  */
#define U_LatinCapitalLetterHWithCaron                  0x021E  /*  */
#define U_LatinSmallLetterHWithCaron                    0x021F  /*  */
#define U_LatinCapitalLetterNWithLongRightLeg           0x0220  /*  */
#define U_Latin_0221                                    0xFFFF  /* RESERVED */
#define U_LatinCapitalLetterOU                          0x0222  /*  */
#define U_LatinSmallLetterOU                            0x0223  /*  */
#define U_LatinCapitalLetterZWithHook                   0x0224  /*  */
#define U_LatinSmallLetterZWithHook                     0x0225  /*  */
#define U_LatinCapitalLetterAWithDotAbove               0x0226  /*  */
#define U_LatinSmallLetterAWithDotAbove                 0x0227  /*  */
#define U_LatinCapitalLetterEWithCedilla                0x0228  /*  */
#define U_LatinSmallLetterEWithCedilla                  0x0229  /*  */

   /* ------ Additions for Livonian: ------ */

#define U_LatinCapitalLetterOWithDiaeresisAndMacron     0x022A  /*  */
#define U_LatinSmallLetterOWithDiaeresisAndMacron       0x022B  /*  */
#define U_LatinCapitalLetterOWithTildeAndMacron         0x022C  /*  */
#define U_LatinSmallLetterOWithTildeAndMacron           0x022D  /*  */
#define U_LatinCapitalLetterOWithDotAbove               0x022E  /*  */
#define U_LatinSmallLetterOWithDotAbove                 0x022F  /*  */
#define U_LatinCapitalLetterOWithDotAboveAndMacron      0x0230  /*  */
#define U_LatinSmallLetterOWithDotAboveAndMacron        0x0231  /*  */
#define U_LatinCapitalLetterYWithMacron                 0x0232  /*  */
#define U_LatinSmallLetterYWithMacron                   0x0233  /*  */
/* #define U_Latin...    RESERVED                       0x0234      */
/* #define U_Latin...    RESERVED                       0x0235      */
/* #define U_Latin...    RESERVED                       0x0236      */
/* #define U_Latin...    RESERVED                       0x0237      */
/* #define U_Latin...    RESERVED                       0x0238      */
/* #define U_Latin...    RESERVED                       0x0239      */
/* #define U_Latin...    RESERVED                       0x023A      */
/* #define U_Latin...    RESERVED                       0x023B      */
/* #define U_Latin...    RESERVED                       0x023C      */
/* #define U_Latin...    RESERVED                       0x023D      */
/* #define U_Latin...    RESERVED                       0x023E      */
/* #define U_Latin...    RESERVED                       0x023F      */
/* #define U_Latin...    RESERVED                       0x0240      */
/* #define U_Latin...    RESERVED                       0x0241      */
/* #define U_Latin...    RESERVED                       0x0242      */
/* #define U_Latin...    RESERVED                       0x0243      */
/* #define U_Latin...    RESERVED                       0x0244      */
/* #define U_Latin...    RESERVED                       0x0245      */
/* #define U_Latin...    RESERVED                       0x0246      */
/* #define U_Latin...    RESERVED                       0x0247      */
/* #define U_Latin...    RESERVED                       0x0248      */
/* #define U_Latin...    RESERVED                       0x0249      */
/* #define U_Latin...    RESERVED                       0x024A      */
/* #define U_Latin...    RESERVED                       0x024B      */
/* #define U_Latin...    RESERVED                       0x024C      */
/* #define U_Latin...    RESERVED                       0x024D      */
/* #define U_Latin...    RESERVED                       0x024E      */
/* #define U_Latin...    RESERVED                       0x024F      */


   /* ====== More Unicode character groups defined in general ====== */
   /*       (set defines where you need them)                        */

   /* ------ 0250-02AF: IPA Extensions ------ */

   /* ------ 02B0-02FF: Spacing Modifier Letters ------ */

   /*        Phonetic modifiers derived from Latin letters: */
#define U_ModifierLetterSmallH                          0x02B0
#define U_ModifierLetterSmallHWithHook                  0x02B1
#define U_ModifierLetterSmallJ                          0x02B2
#define U_ModifierLetterSmallR                          0x02B3
#define U_ModifierLetterSmallTurnedR                    0x02B4
#define U_ModifierLetterSmallTurnedRWithHook            0x02B5
#define U_ModifierLetterSmallCapitalInvertedR           0x02B6
#define U_ModifierLetterSmallW                          0x02B7
#define U_ModifierLetterSmallY                          0x02B8

   /*        Miscellaneous phonetic modifiers: */
#define U_ModifierLetterPrime                           0x02B9
#define U_ModifierLetterDoublePrime                     0x02BA
#define U_ModifierLetterTurnedComma                     0x02BB
#define U_ModifierLetterApostrophe                      0x02BC
#define U_ModifierLetterReversedComma                   0x02BD
#define U_ModifierLetterRightHalfRing                   0x02BE
#define U_ModifierLetterLeftHalfRing                    0x02BF
#define U_ModifierLetterGlottalStop                     0x02C0
#define U_ModifierLetterReversedGlottalStop             0x02C1
#define U_ModifierLetterLeftArrowhead                   0x02C2
#define U_ModifierLetterRightArrowhead                  0x02C3
#define U_ModifierLetterUpArrowhead                     0x02C4
#define U_ModifierLetterDownArrowhead                   0x02C5
#define U_ModifierLetterCircumflexAccent                0x02C6
#define U_Caron                                         0x02C7
#define U_ModifierLetterVerticalLine                    0x02C8
#define U_ModifierLetterMacron                          0x02C9
#define U_ModifierLetterAcuteAccent                     0x02CA
#define U_ModifierLetterGraveAccent                     0x02CB
#define U_ModifierLetterLowVerticalLine                 0x02CC
#define U_ModifierLetterLowMacron                       0x02CD
#define U_ModifierLetterLowGraveAccent                  0x02CE
#define U_ModifierLetterLowAcuteAccent                  0x02CF
#define U_ModifierLetterTriangularColon                 0x02D0
#define U_ModifierLetterHalfTriangularColon             0x02D1
#define U_ModifierLetterCentredRightHalfRing            0x02D2
#define U_ModifierLetterCentredLeftHalfRing             0x02D3
#define U_ModifierLetterUpTack                          0x02D4
#define U_ModifierLetterDownTack                        0x02D5
#define U_ModifierLetterPlusSign                        0x02D6
#define U_ModifierLetterMinusSign                       0x02D7

   /*        Spacing clones of diacritics: */
#define U_Breve                                         0x02D8
#define U_DotAbove                                      0x02D9
#define U_RingAbove                                     0x02DA
#define U_Ogonek                                        0x02DB
#define U_SmallTilde                                    0x02DC
#define U_DoubleAcuteAccent                             0x02DD

   /*        Additions based on 1989 IPA: */
#define U_ModifierLetterRhoticHook                      0x02DE
#define U_ModifierLetterCrossAccent                     0x02DF
#define U_ModifierLetterSmallGamma                      0x02E0
#define U_ModifierLetterSmallL                          0x02E1
#define U_ModifierLetterSmallS                          0x02E2
#define U_ModifierLetterSmallX                          0x02E3
#define U_ModifierLetterSmallReversedGlottalStop        0x02E4

   /*        Tone letters: */
#define U_ModifierLetterExtraHighToneBar                0x02E5
#define U_ModifierLetterHighToneBar                     0x02E6
#define U_ModifierLetterMidToneBar                      0x02E7
#define U_ModifierLetterLowToneBar                      0x02E8
#define U_ModifierLetterExtraLowToneBar                 0x02E9
#define U_ModifierLetterYinDepartingToneMark            0x02EA
#define U_ModifierLetterYangDepartingToneMark           0x02EB

   /*        IPA modifiers: */
#define U_ModifierLetterVoicing                         0x02EC
#define U_ModifierLetterUnaspiraced                     0x02ED

   /*        Other modifier letters: */
#define U_ModifierLetterDoubleApostrophe                0x02EE
/* 0x02EF ... 0x02FF ==  RESERVED */


   /* ------ 0300-036F: Combining Diacritical Marks ------ */

   /*        Ordinary diacritics: */
#define U_CombiningGraveAccent                          0x0300
#define U_CombiningAcuteAccent                          0x0301
#define U_CombiningCircumflexAccent                     0x0302
#define U_CombiningTilde                                0x0303
#define U_CombiningMacron                               0x0304
#define U_CombiningOverline                             0x0305
#define U_CombiningBreve                                0x0306
#define U_CombiningDotAbove                             0x0307
#define U_CombiningDiaeresis                            0x0308
#define U_CombiningHookAbove                            0x0309
#define U_CombiningRingAbove                            0x030A
#define U_CombiningDoubleAcuteAccent                    0x030B
#define U_CombiningCaron                                0x030C
#define U_CombiningVerticalLineAbove                    0x030D
#define U_CombiningDoubleVerticalLine                   0x030E
#define U_CombiningDoubleGraveAccent                    0x030F
#define U_CombiningCandrabindu                          0x0310
#define U_CombiningInvertedBreve                        0x0311
#define U_CombiningTurnedCommaAbove                     0x0312
#define U_CombiningCommaAbove                           0x0313
#define U_CombiningReversedCommaAbove                   0x0314
#define U_CombiningCommaAboveRight                      0x0315
#define U_CombiningGraveAccentBelow                     0x0316
#define U_CombiningAcuteAccentBelow                     0x0317
#define U_CombiningLeftTackBelow                        0x0318
#define U_CombiningRightTackBelow                       0x0319
#define U_CombiningLeftAngleAbove                       0x031A
#define U_CombiningHorn                                 0x031B
#define U_CombiningLeftHalfRingBelow                    0x031C
#define U_CombiningUpTackBelow                          0x031D
#define U_CombiningDownTackBelow                        0x031E
#define U_CombiningPlusSignBelow                        0x031F
#define U_CombiningMinusSignBelow                       0x0320
#define U_CombiningPalatalizedHookBelow                 0x0321
#define U_CombiningRetroflexHookBelow                   0x0322
#define U_CombiningDotBelow                             0x0323
#define U_CombiningDiaeresisBelow                       0x0324
#define U_CombiningRingBelow                            0x0325
#define U_CombiningCommaBelow                           0x0326
#define U_CombiningCedilla                              0x0327
#define U_CombiningOgonek                               0x0328
#define U_CombiningVerticalLineBelow                    0x0329
#define U_CombiningBridgeBelow                          0x032A
#define U_CombiningInvertedDoubleArchBelow              0x032B
#define U_CombiningCaronBelow                           0x032C
#define U_CombiningCircumflexAccentBelow                0x032D
#define U_CombiningBreveBelow                           0x032E
#define U_CombiningInvertedBreveBelow                   0x032F
#define U_CombiningTildeBelow                           0x0330
#define U_CombiningMacronBelow                          0x0331
#define U_CombiningLowLine                              0x0332
#define U_CombiningDoubleLowLine                        0x0333

   /*        Overstruck diacritics: */
#define U_CombiningTildeOverlay                         0x0334
#define U_CombiningShortStrokeOverlay                   0x0335
#define U_CombiningLongStrokeOverlay                    0x0336
#define U_CombiningShortSolidusOverlay                  0x0337
#define U_CombiningLongSolidusOverlay                   0x0338

   /*        Additions: */
#define U_CombiningRightHalfRingBelow                   0x0339
#define U_CombiningInvertedBridgeBelow                  0x033A
#define U_CombiningSquareBelow                          0x033B
#define U_CombiningSeagullBelow                         0x033C
#define U_CombiningXAbove                               0x033D
#define U_CombiningVerticalTilde                        0x033E
#define U_CombiningDoubleOverline                       0x033F

   /*        Vietnamese tone marks (deprecated): */
#define U_CombiningGraveToneMark                        0x0340
#define U_CombiningAcuteToneMark                        0x0341

   /*        Additions for Greek: */
#define U_CombiningGreekPerispomeni                     0x0342
#define U_CombiningGreekKoronis                         0x0343
#define U_CombiningGreekDialytikaTonos                  0x0344
#define U_CombiningGreekNonSpacingIotaBelow             0x0345

   /*        Additions for IPA: */
#define U_CombiningBridgeAbove                          0x0346
#define U_CombiningQeualsSignBelow                      0x0347
#define U_CombiningDoubleVerticalLineBelow              0x0348
#define U_CombiningLeftAngleBelow                       0x0349
#define U_CombiningNotTildeAbove                        0x034A

   /*        IPA diacritics for disordered speech: */
#define U_CombiningHomotheticAboce                      0x034B
#define U_CombiningAlmostEqualToAbove                   0x034C
#define U_CombiningLeftRightArrowBelow                  0x034D
#define U_CombiningUpwardsArrowBelow                    0x034E

   /*        Grapheme joiner: */
#define U_CombiningGraphemeJoiner                       0x034F

   /*        Double diacritics: */
#define U_CombiningDoubleTilde                          0x0350
#define U_CombiningDoubleInvertedBreve                  0x0351
#define U_CombiningDoubleRightwardsArrowBelow           0x0352

   /*        Medieval superscript letter diacritics: */
#define U_CombiningLatinSmallLetterA                    0x0353
#define U_CombiningLatinSmallLetterE                    0x0354
#define U_CombiningLatinSmallLetterI                    0x0355
#define U_CombiningLatinSmallLetterO                    0x0356
#define U_CombiningLatinSmallLetterU                    0x0357
#define U_CombiningLatinSmallLetterC                    0x0358
#define U_CombiningLatinSmallLetterD                    0x0359
#define U_CombiningLatinSmallLetterH                    0x035A
#define U_CombiningLatinSmallLetterM                    0x035B
#define U_CombiningLatinSmallLetterR                    0x035C
#define U_CombiningLatinSmallLetterT                    0x035D
#define U_CombiningLatinSmallLetterV                    0x035E
#define U_CombiningLatinSmallLetterX                    0x035F


   /* ------ 0370-03FF: Greek and Coptic ------ */

   /*        Archaic letters: */
#define U_GreekCapitalLetterHeta                        0x0370
#define U_GreekSmallLetterHeta                          0x0371
#define U_GreekCapitalLetterArchaicSampi                0x0372
#define U_GreekSmallLetterArchaicSampi                  0x0373

   /*        Numeral signs: */
#define U_GreekNumeralSign                              0x0374
#define U_GreekLowerNumeralSign                         0x0375

   /*        Archaic letters: */
#define U_GreekCapitalLetterPamphylianDigamma           0x0376
#define U_GreekSmallLetterPamphylianDigamma             0x0377

   /*        Iota subscript: */
#define U_GreekYpogegrammeni                            0x037A

   /*        Lowercase of editorial symbols: */
#define U_GreekSmallReversedLunateSigmaSymbol           0x037B
#define U_GreekSmallDottedLunateSigmaSymbol             0x037C
#define U_GreekSmallReversedDottedLunateSigmaSymbol     0x037D

   /*        Punctuation: */
#define U_GreekQuestionMark                             0x037E

   /*        Spacing accent marks: */
#define U_GreekTonus                                    0x0384
#define U_GreekDialytikaTonos                           0x0385

   /*        Letter: */
#define U_GreekCapitalLetterAlphaWithTonos              0x0386

   /*        Punctuation: */
#define U_GreekAnoTeleia                                0x0387

   /*        Letter: */
#define U_GreekCapitalLetterEpsilonWithTonos            0x0388
#define U_GreekCapitalLetterEtaWithTonos                0x0389
#define U_GreekCapitalLetterIotaWithTonos               0x038A
/* #define U_Greekxxx                                   0x038B */  /* reserved */
#define U_GreekCapitalLetterOmicronWithTonos            0x038C
/* #define U_Greekxxx                                   0x038D */  /* reserved */
#define U_GreekCapitalLetterUpsilonWithTonos            0x038E
#define U_GreekCapitalLetterOmegaWithTonos              0x038F
#define U_GreekSmallLetterIotaWithDialytikaAndTonos     0x0390
#define U_GreekCapitalLetterAlpha                       0x0391
#define U_GreekCapitalLetterBeta                        0x0392
#define U_GreekCapitalLetterGamma                       0x0393
#define U_GreekCapitalLetterDelta                       0x0394
#define U_GreekCapitalLetterEpsilon                     0x0395
#define U_GreekCapitalLetterZeta                        0x0396
#define U_GreekCapitalLetterEta                         0x0397
#define U_GreekCapitalLetterTheta                       0x0398
#define U_GreekCapitalLetterIota                        0x0399
#define U_GreekCapitalLetterKappa                       0x039A
#define U_GreekCapitalLetterLambda                      0x039B
#define U_GreekCapitalLetterMu                          0x039C
#define U_GreekCapitalLetterNu                          0x039D
#define U_GreekCapitalLetterXi                          0x039E
#define U_GreekCapitalLetterOmicron                     0x039F
#define U_GreekCapitalLetterPi                          0x03A0
#define U_GreekCapitalLetterRho                         0x03A1
/* 0x03A2 ==  RESERVED */
#define U_GreekCapitalLetterSigma                       0x03A3
#define U_GreekCapitalLetterTau                         0x03A4
#define U_GreekCapitalLetterUpsilon                     0x03A5
#define U_GreekCapitalLetterPhi                         0x03A6
#define U_GreekCapitalLetterChi                         0x03A7
#define U_GreekCapitalLetterPsi                         0x03A8
#define U_GreekCapitalLetterOmega                       0x03A9
#define U_GreekCapitalLetterIotaWithDialytika           0x03AA
#define U_GreekCapitalLetterUpsilonWithDialytika        0x03AB
#define U_GreekSmallLetterAlphaWithTonos                0x03AC
#define U_GreekSmallLetterEpsilonWithTonos              0x03AD
#define U_GreekSmallLetterEtaWithTonos                  0x03AE
#define U_GreekSmallLetterIotaWithTonos                 0x03AF
#define U_GreekSmallLetterUpsilonWithDialytikaAndTonos  0x03B0
#define U_GreekSmallLetterAlpha                         0x03B1
#define U_GreekSmallLetterBeta                          0x03B2
#define U_GreekSmallLetterGamma                         0x03B3
#define U_GreekSmallLetterDelta                         0x03B4
#define U_GreekSmallLetterEpsilon                       0x03B5
#define U_GreekSmallLetterZeta                          0x03B6
#define U_GreekSmallLetterEta                           0x03B7
#define U_GreekSmallLetterTheta                         0x03B8
#define U_GreekSmallLetterIota                          0x03B9
#define U_GreekSmallLetterKappa                         0x03BA
#define U_GreekSmallLetterLambda                        0x03BB
#define U_GreekSmallLetterMu                            0x03BC
#define U_GreekSmallLetterNu                            0x03BD
#define U_GreekSmallLetterXi                            0x03BE
#define U_GreekSmallLetterOmicron                       0x03BF
#define U_GreekSmallLetterPi                            0x03C0
#define U_GreekSmallLetterRho                           0x03C1
#define U_GreekSmallLetterFinalSigma                    0x03C2
#define U_GreekSmallLetterSigma                         0x03C3
#define U_GreekSmallLetterTau                           0x03C4
#define U_GreekSmallLetterUpsilon                       0x03C5
#define U_GreekSmallLetterPhi                           0x03C6
#define U_GreekSmallLetterChi                           0x03C7
#define U_GreekSmallLetterPsi                           0x03C8
#define U_GreekSmallLetterOmega                         0x03C9
#define U_GreekSmallLetterIotaWithDialytika             0x03CA
#define U_GreekSmallLetterUpsilonWithDialytika          0x03CB
#define U_GreekSmallLetterOmicronWithTonos              0x03CC
#define U_GreekSmallLetterUpsilonWithTonos              0x03CD
#define U_GreekSmallLetterOmegaWithTonos                0x03CE

   /*        Variant letterforms: */
#define U_GreekCapitalKaiSymbol                         0x03CF
#define U_GreekBetaSymbol                               0x03D0
#define U_GreekThetaSymbol                              0x03D1
#define U_GreekUpsilonWithHookSymbol                    0x03D2
#define U_GreekUpsilonWithAcuteAndHookSymbol            0x03D3
#define U_GreekUpsilonWithDiaeresisAndHookSymbol        0x03D4
#define U_GreekPhiSymbol                                0x03D5
#define U_GreekPiSymbol                                 0x03D6
#define U_GreekKaiSymbol                                0x03D7

   /*        Archaic letters: */
#define U_GreekLetterArchaicKoppa                       0x03D8
#define U_GreekSmallLetterArchaicKoppa                  0x03D9
#define U_GreekLetterStigma                             0x03DA
#define U_GreekSmallLetterStigma                        0x03DB
#define U_GreekLetterDigamma                            0x03DC
#define U_GreekSmallLetterDigamma                       0x03DD
#define U_GreekLetterKoppa                              0x03DE
#define U_GreekSmallLetterKoppa                         0x03DF
#define U_GreekLetterSampi                              0x03E0
#define U_GreekSmallLetterSampi                         0x03E1

   /*        Coptic letters derived from Demotic: */
#define U_CopticCapitalLetterShei                       0x03E2
#define U_CopticSmallLetterShei                         0x03E3
#define U_CopticCapitalLetterFei                        0x03E4
#define U_CopticSmallLetterFei                          0x03E5
#define U_CopticCapitalLetterKhei                       0x03E6
#define U_CopticSmallLetterKhei                         0x03E7
#define U_CopticCapitalLetterHori                       0x03E8
#define U_CopticSmallLetterHori                         0x03E9
#define U_CopticCapitalLetterGangia                     0x03EA
#define U_CopticSmallLetterGangia                       0x03EB
#define U_CopticCapitalLetterShima                      0x03EC
#define U_CopticSmallLetterShima                        0x03ED
#define U_CopticCapitalLetterDei                        0x03EE
#define U_CopticSmallLetterDei                          0x03EF

   /*        Variant letterforms: */
#define U_GreekKappaSymbol                              0x03F0
#define U_GreekRhoSymbol                                0x03F1
#define U_GreekLunateSigmaSymbol                        0x03F2

   /*        Additional letter: */
#define U_GreekLetterYot                                0x03F3

   /*        Variant letterforms and symbols: */
#define U_GreekCapitalThetaSymbol                       0x03F4
#define U_GreekLunateEpsilonSymbol                      0x03F5
#define U_GreekReversedLunateEpsilonSymbol              0x03F6

   /*        Additional archaic letters for Bactrian: */
#define U_GreekCapitalLetterSho                         0x03F7
#define U_GreekSmallLetterSho                           0x03F8

   /*        Variant Letterform: */
#define U_GreekCapitalLunateSigmaSymbol                 0x03F9

   /*        Archaic letters: */
#define U_GreekCapitalLetterSan                         0x03FA
#define U_GreekSmallLetterSan                           0x03FB

   /*        Symbol: */
#define U_GreekRhoWithStrokeSymbol                      0x03FC

   /*        Editorial symbols: */
#define U_GreekCapitalReversedLunateSigmaSymbol         0x03FD
#define U_GreekCapitalDottedLunateSigmaSymbol           0x03FE
#define U_GreekCapitalReversedDottedLunateSigmaSymbol   0x03FF

   /* ------ 0400-04FF: Cyrillic ------ */

   /*        Cyrillic extensions: */
#define U_CyrillicCapitalLetterIeWithGrave              0x0400
#define U_CyrillicCapitalLetterIo                       0x0401
#define U_CyrillicCapitalLetterDje                      0x0402
#define U_CyrillicCapitalLetterGje                      0x0403
#define U_CyrillicCapitalLetterUkrainianIe              0x0404
#define U_CyrillicCapitalLetterDze                      0x0405
#define U_CyrillicCapitalLetterByelorussianUkrainianI   0x0406
#define U_CyrillicCapitalLetterYi                       0x0407
#define U_CyrillicCapitalLetterJe                       0x0408
#define U_CyrillicCapitalLetterLje                      0x0409
#define U_CyrillicCapitalLetterNje                      0x040A
#define U_CyrillicCapitalLetterTshe                     0x040B
#define U_CyrillicCapitalLetterKje                      0x040C
#define U_CyrillicCapitalLetterIWithGrave               0x040D
#define U_CyrillicCapitalLetterShortU                   0x040E
#define U_CyrillicCapitalLetterDzhe                     0x040F

   /*        Basic Russian alphabet: */
#define U_CyrillicCapitalLetterA                        0x0410
#define U_CyrillicCapitalLetterBe                       0x0411
#define U_CyrillicCapitalLetterVe                       0x0412
#define U_CyrillicCapitalLetterGhe                      0x0413
#define U_CyrillicCapitalLetterDe                       0x0414
#define U_CyrillicCapitalLetterIe                       0x0415
#define U_CyrillicCapitalLetterZhe                      0x0416
#define U_CyrillicCapitalLetterZe                       0x0417
#define U_CyrillicCapitalLetterI                        0x0418
#define U_CyrillicCapitalLetterShortI                   0x0419
#define U_CyrillicCapitalLetterKa                       0x041A
#define U_CyrillicCapitalLetterEl                       0x041B
#define U_CyrillicCapitalLetterEm                       0x041C
#define U_CyrillicCapitalLetterEn                       0x041D
#define U_CyrillicCapitalLetterO                        0x041E
#define U_CyrillicCapitalLetterPe                       0x041F
#define U_CyrillicCapitalLetterEr                       0x0420
#define U_CyrillicCapitalLetterEs                       0x0421
#define U_CyrillicCapitalLetterTe                       0x0422
#define U_CyrillicCapitalLetterU                        0x0423
#define U_CyrillicCapitalLetterEf                       0x0424
#define U_CyrillicCapitalLetterHa                       0x0425
#define U_CyrillicCapitalLetterTse                      0x0426
#define U_CyrillicCapitalLetterChe                      0x0427
#define U_CyrillicCapitalLetterSha                      0x0428
#define U_CyrillicCapitalLetterShcha                    0x0429
#define U_CyrillicCapitalLetterHardSign                 0x042A
#define U_CyrillicCapitalLetterYeru                     0x042B
#define U_CyrillicCapitalLetterSoftSign                 0x042C
#define U_CyrillicCapitalLetterE                        0x042D
#define U_CyrillicCapitalLetterYu                       0x042E
#define U_CyrillicCapitalLetterYa                       0x042F

#define U_CyrillicSmallLetterA                          0x0430
#define U_CyrillicSmallLetterBe                         0x0431
#define U_CyrillicSmallLetterVe                         0x0432
#define U_CyrillicSmallLetterGhe                        0x0433
#define U_CyrillicSmallLetterDe                         0x0434
#define U_CyrillicSmallLetterIe                         0x0435
#define U_CyrillicSmallLetterZhe                        0x0436
#define U_CyrillicSmallLetterZe                         0x0437
#define U_CyrillicSmallLetterI                          0x0438
#define U_CyrillicSmallLetterShortI                     0x0439
#define U_CyrillicSmallLetterKa                         0x043A
#define U_CyrillicSmallLetterEl                         0x043B
#define U_CyrillicSmallLetterEm                         0x043C
#define U_CyrillicSmallLetterEn                         0x043D
#define U_CyrillicSmallLetterO                          0x043E
#define U_CyrillicSmallLetterPe                         0x043F
#define U_CyrillicSmallLetterEr                         0x0440
#define U_CyrillicSmallLetterEs                         0x0441
#define U_CyrillicSmallLetterTe                         0x0442
#define U_CyrillicSmallLetterU                          0x0443
#define U_CyrillicSmallLetterEf                         0x0444
#define U_CyrillicSmallLetterHa                         0x0445
#define U_CyrillicSmallLetterTse                        0x0446
#define U_CyrillicSmallLetterChe                        0x0447
#define U_CyrillicSmallLetterSha                        0x0448
#define U_CyrillicSmallLetterShcha                      0x0449
#define U_CyrillicSmallLetterHardSign                   0x044A
#define U_CyrillicSmallLetterYeru                       0x044B
#define U_CyrillicSmallLetterSoftSign                   0x044C
#define U_CyrillicSmallLetterE                          0x044D
#define U_CyrillicSmallLetterYu                         0x044E
#define U_CyrillicSmallLetterYa                         0x044F

   /*        Cyrillic extensions: */
#define U_CyrillicSmallLetterIeWithGrave                0x0450
#define U_CyrillicSmallLetterIo                         0x0451
#define U_CyrillicSmallLetterDje                        0x0452
#define U_CyrillicSmallLetterGje                        0x0453
#define U_CyrillicSmallLetterUkrainianIe                0x0454
#define U_CyrillicSmallLetterDze                        0x0455
#define U_CyrillicSmallLetterByelorussianUkrainianI     0x0456
#define U_CyrillicSmallLetterYi                         0x0457
#define U_CyrillicSmallLetterJe                         0x0458
#define U_CyrillicSmallLetterLje                        0x0459
#define U_CyrillicSmallLetterNje                        0x045A
#define U_CyrillicSmallLetterTshe                       0x045B
#define U_CyrillicSmallLetterKje                        0x045C
#define U_CyrillicSmallLetterIWithGrave                 0x045D
#define U_CyrillicSmallLetterShortU                     0x045E
#define U_CyrillicSmallLetterDzhe                       0x045F

   /*        Cyrillic extensions: */
#define U_CyrillicCapitalLetterOmega                    0x0460
#define U_CyrillicSmallLetterOmega                      0x0461
#define U_CyrillicCapitalLetterYat                      0x0462
#define U_CyrillicSmallLetterYat                        0x0463
#define U_CyrillicCapitalLetterIotifiedE                0x0464
#define U_CyrillicSmallLetterIotifiedE                  0x0465
#define U_CyrillicCapitalLetterLittleYus                0x0466
#define U_CyrillicSmallLetterLittleYus                  0x0467
#define U_CyrillicCapitalLetterIotifiedLittleYus        0x0468
#define U_CyrillicSmallLetterIotifiedLittleYus          0x0469
#define U_CyrillicCapitalLetterBigYus                   0x046A
#define U_CyrillicSmallLetterBigYus                     0x046B
#define U_CyrillicCapitalLetterIotifiedBigYus           0x046C
#define U_CyrillicSmallLetterIotifiedBigYus             0x046D
#define U_CyrillicCapitalLetterKsi                      0x046E
#define U_CyrillicSmallLetterKsi                        0x046F
#define U_CyrillicCapitalLetterPsi                      0x0470
#define U_CyrillicSmallLetterPsi                        0x0471
#define U_CyrillicCapitalLetterFita                     0x0472
#define U_CyrillicSmallLetterFita                       0x0473
#define U_CyrillicCapitalLetterIzhitsa                  0x0474
#define U_CyrillicSmallLetterIzhitsa                    0x0475
#define U_CyrillicCapitalLetterIzhitsaWithDoubleGraveAccent    0x0476
#define U_CyrillicSmallLetterIzhitsaWithDoubleGraveAccent      0x0477
#define U_CyrillicCapitalLetterUk                       0x0478
#define U_CyrillicSmallLetterUk                         0x0479
#define U_CyrillicCapitalLetterRoundOmega               0x047A
#define U_CyrillicSmallLetterRoundOmega                 0x047B
#define U_CyrillicCapitalLetterOmegaWithTitlo           0x047C
#define U_CyrillicSmallLetterOmegaWithTitlo             0x047D
#define U_CyrillicCapitalLetterOt                       0x047E
#define U_CyrillicSmallLetterOt                         0x047F
#define U_CyrillicCapitalLetterKoppa                    0x0480
#define U_CyrillicSmallLetterKoppa                      0x0481

   /*        Cyrillic extensions: */
#define U_CyrillicThousandsSign                         0x0482
#define U_CombiningCyrillicTitlo                        0x0483
#define U_CombiningCyrillicPalatalization               0x0484
#define U_CombiningCyrillicDasiaPneumata                0x0485
#define U_CombiningCyrillicPsiliPneumata                0x0486
#define U_CombiningCyrillicPokrytie                     0x0487
#define U_CombiningCyrillicHundredThousandsSign         0x0488
#define U_CombiningCyrillicMillionsSign                 0x0489

   /*        Extended Cyrillic: */
#define U_CyrillicCapitalLetterShortIWithTail           0x048A
#define U_CyrillicSmallLetterShortIWithTail             0x048B
#define U_CyrillicCapitalLetterSemisoftSign             0x048C
#define U_CyrillicSmallLetterSemisoftSign               0x048D
#define U_CyrillicCapitalLetterErWithTick               0x048E
#define U_CyrillicSmallLetterErWithTick                 0x048F
#define U_CyrillicCapitalLetterGheWithUpturn            0x0490
#define U_CyrillicSmallLetterGheWithUpturn              0x0491
#define U_CyrillicCapitalLetterGheWithStroke            0x0492
#define U_CyrillicSmallLetterGheWithStroke              0x0493
#define U_CyrillicCapitalLetterGheWithMiddleHook        0x0494
#define U_CyrillicSmallLetterGheWithMiddleHook          0x0495
#define U_CyrillicCapitalLetterZheWithDescender         0x0496
#define U_CyrillicSmallLetterZheWithDescender           0x0497
#define U_CyrillicCapitalLetterZeWithDescender          0x0498
#define U_CyrillicSmallLetterZeWithDescender            0x0499
#define U_CyrillicCapitalLetterKaWithDescender          0x049A
#define U_CyrillicSmallLetterKaWithDescender            0x049B
#define U_CyrillicCapitalLetterKaWithVerticalStroke     0x049C
#define U_CyrillicSmallLetterKaWithVerticalStroke       0x049D
#define U_CyrillicCapitalLetterKaWithStroke             0x049E
#define U_CyrillicSmallLetterKaWithStroke               0x049F
#define U_CyrillicCapitalLetterBashkirKa                0x04A0
#define U_CyrillicSmallLetterBashkirKa                  0x04A1
#define U_CyrillicCapitalLetterEnWithDescender          0x04A2
#define U_CyrillicSmallLetterEnWithDescender            0x04A3
#define U_CyrillicCapitalLigatureEnGhe                  0x04A4
#define U_CyrillicSmallLigatureEnGhe                    0x04A5
#define U_CyrillicCapitalLetterPeWithMiddleHook         0x04A6
#define U_CyrillicSmallLetterPeWithMiddleHook           0x04A7
#define U_CyrillicCapitalLetterAbkhasianHa              0x04A8
#define U_CyrillicSmallLetterAbkhasianHa                0x04A9
#define U_CyrillicCapitalLetterEsWithDescender          0x04AA
#define U_CyrillicSmallLetterEsWithDescender            0x04AB
#define U_CyrillicCapitalLetterTeWithDescender          0x04AC
#define U_CyrillicSmallLetterTeWithDescender            0x04AD
#define U_CyrillicCapitalLetterStraightU                0x04AE
#define U_CyrillicSmallLetterStraightU                  0x04AF
#define U_CyrillicCapitalLetterStraightUWithStroke      0x04B0
#define U_CyrillicSmallLetterStraightUWithStroke        0x04B1
#define U_CyrillicCapitalLetterHaWithDescender          0x04B2
#define U_CyrillicSmallLetterHaWithDescender            0x04B3
#define U_CyrillicCapitalLigatureTeTse                  0x04B4
#define U_CyrillicSmallLigatureTeTse                    0x04B5
#define U_CyrillicCapitalLetterCheWithDescender         0x04B6
#define U_CyrillicSmallLetterCheWithDescender           0x04B7
#define U_CyrillicCapitalLetterCheWithVerticalStroke    0x04B8
#define U_CyrillicSmallLetterCheWithVerticalStroke      0x04B9
#define U_CyrillicCapitalLetterShha                     0x04BA
#define U_CyrillicSmallLetterShha                       0x04BB
#define U_CyrillicCapitalLetterAbkhasianChe             0x04BC
#define U_CyrillicSmallLetterAbkhasianChe               0x04BD
#define U_CyrillicCapitalLetterAbkhasianCheWithDescender    0x04BE
#define U_CyrillicSmallLetterAbkhasianCheWithDescender      0x04BF

#define U_CyrillicLetterPalochka                        0x04C0
#define U_CyrillicCapitalLetterZheWithBreve             0x04C1
#define U_CyrillicSmallLetterZheWithBreve               0x04C2
#define U_CyrillicCapitalLetterKaWithHook               0x04C3
#define U_CyrillicSmallLetterKaWithHook                 0x04C4
#define U_CyrillicCapitalLetterElWithTail               0x04C5
#define U_CyrillicSmallLetterElWithTail                 0x04C6
#define U_CyrillicCapitalLetterEnWithHook               0x04C7
#define U_CyrillicSmallLetterEnWithHook                 0x04C8
#define U_CyrillicCapitalLetterEnWithTail               0x04C9
#define U_CyrillicSmallLetterEnWithTail                 0x04CA
#define U_CyrillicCapitalLetterKhakassianChe            0x04CB
#define U_CyrillicSmallLetterKhakassianChe              0x04CC
#define U_CyrillicCapitalLetterEmWithTail               0x04CD
#define U_CyrillicSmallLetterEmWithTail                 0x04CE
#define U_CyrillicSmallLetterPalochka                   0x04CF
#define U_CyrillicCapitalLetterAWithBreve               0x04D0
#define U_CyrillicSmallLetterAWithBreve                 0x04D1
#define U_CyrillicCapitalLetterAWithDiaeresis           0x04D2
#define U_CyrillicSmallLetterAWithDiaeresis             0x04D3
#define U_CyrillicCapitalLigatureAIe                    0x04D4
#define U_CyrillicSmallLigatureAIe                      0x04D5
#define U_CyrillicCapitalLetterIeWithBreve              0x04D6
#define U_CyrillicSmallLetterIeWithBreve                0x04D7
#define U_CyrillicCapitalLetterSchwa                    0x04D8
#define U_CyrillicSmallLetterSchwa                      0x04D9
#define U_CyrillicCapitalLetterSchwaWithDiaeresis       0x04DA
#define U_CyrillicSmallLetterSchwaWithDiaeresis         0x04DB
#define U_CyrillicCapitalLetterZheWithDiaeresis         0x04DC
#define U_CyrillicSmallLetterZheWithDiaeresis           0x04DD
#define U_CyrillicCapitalLetterZeWithDiaeresis          0x04DE
#define U_CyrillicSmallLetterZeWithDiaeresis            0x04DF
#define U_CyrillicCapitalLetterAbkhasianDze             0x04E0
#define U_CyrillicSmallLetterAbkhasianDze               0x04E1
#define U_CyrillicCapitalLetterIWithMacron              0x04E2
#define U_CyrillicSmallLetterIWithMacron                0x04E3
#define U_CyrillicCapitalLetterIWithDiaeresis           0x04E4
#define U_CyrillicSmallLetterIWithDiaeresis             0x04E5
#define U_CyrillicCapitalLetterOWithDiaeresis           0x04E6
#define U_CyrillicSmallLetterOWithDiaeresis             0x04E7
#define U_CyrillicCapitalLetterBarredO                  0x04E8
#define U_CyrillicSmallLetterBarredO                    0x04E9
#define U_CyrillicCapitalLetterBarredOWithDiaeresis     0x04EA
#define U_CyrillicSmallLetterBarredOWithDiaeresis       0x04EB
#define U_CyrillicCapitalLetterEWithDiaeresis           0x04EC
#define U_CyrillicSmallLetterEWithDiaeresis             0x04ED
#define U_CyrillicCapitalLetterUWithMacron              0x04EE
#define U_CyrillicSmallLetterUWithMacron                0x04EF
#define U_CyrillicCapitalLetterUWithDiaeresis           0x04F0
#define U_CyrillicSmallLetterUWithDiaeresis             0x04F1
#define U_CyrillicCapitalLetterUWithDoubleAcute         0x04F2
#define U_CyrillicSmallLetterUWithDoubleAcute           0x04F3
#define U_CyrillicCapitalLetterCheWithDiaeresis         0x04F4
#define U_CyrillicSmallLetterCheWithDiaeresis           0x04F5
#define U_CyrillicCapitalLetterGheWithDescender         0x04F6
#define U_CyrillicSmallLetterGheWithDescender           0x04F7
#define U_CyrillicCapitalLetterYeruWithDiaeresis        0x04F8
#define U_CyrillicSmallLetterYeruWithDiaeresis          0x04F9

   /*        Additions for Nivkh: */
#define U_CyrillicCapitalLetterGheWithStrokeAndHook     0x04FA
#define U_CyrillicSmallLetterGheWithStrokeAndHook       0x04FB
#define U_CyrillicCapitalLetterHaWithHook               0x04FC
#define U_CyrillicSmallLetterHaWithHook                 0x04FD
#define U_CyrillicCapitalLetterHaWithStroke             0x04FE
#define U_CyrillicSmallLetterHaWithStroke               0x04FF


   /* ------ 0500-052F: Cyrillic Supplementary ------ */
   /* ------ 0530-058F: Armenian ------ */
   
   /* ------ 0590-05FF: Hebrew ------ */

   /*        Cantillation marks: */
#define U_HebrewAccentEtnahta                           0x0591
#define U_HebrewAccentSegol                             0x0592
#define U_HebrewAccentShalshelet                        0x0593
#define U_HebrewAccentZaqefQatan                        0x0594
#define U_HebrewAccentZaqefGadol                        0x0595
#define U_HebrewAccentTipeha                            0x0596
#define U_HebrewAccentRevia                             0x0597
#define U_HebrewAccentZarqa                             0x0598
#define U_HebrewAccentPashta                            0x0599
#define U_HebrewAccentYetiv                             0x059A
#define U_HebrewAccentTevir                             0x059B
#define U_HebrewAccentGeresh                            0x059C
#define U_HebrewAccentGereshMuqdam                      0x059D
#define U_HebrewAccentGershayim                         0x059E
#define U_HebrewAccentQarneyPara                        0x059F
#define U_HebrewAccentTelishaGedola                     0x05A0
#define U_HebrewAccentPazer                             0x05A1
#define U_HebrewAccentAtnahHafukh                       0x05A2
#define U_HebrewAccentMunah                             0x05A3
#define U_HebrewAccentMahapakh                          0x05A4
#define U_HebrewAccentMerkha                            0x05A5
#define U_HebrewAccentMerkhaKefula                      0x05A6
#define U_HebrewAccentDarga                             0x05A7
#define U_HebrewAccentQadma                             0x05A8
#define U_HebrewAccentTelishaQetana                     0x05A9
#define U_HebrewAccentYerahBenYomo                      0x05AA
#define U_HebrewAccentOle                               0x05AB
#define U_HebrewAccentIluy                              0x05AC
#define U_HebrewAccentDehi                              0x05AD
#define U_HebrewAccentZinor                             0x05AE
#define U_HebrewMarkasoraCircle                         0x05AF
   
   /*        Points and punctuation: */
#define U_HebrewPointSheva                              0x05B0
#define U_HebrewPointHatafSegol                         0x05B1
#define U_HebrewPointHatafPatah                         0x05B2
#define U_HebrewPointHatafQamats                        0x05B3
#define U_HebrewPointHiriq                              0x05B4
#define U_HebrewPointTsere                              0x05B5
#define U_HebrewPointSegol                              0x05B6
#define U_HebrewPointPatah                              0x05B7
#define U_HebrewPointQamats                             0x05B8
#define U_HebrewPointHolam                              0x05B9
#define U_HebrewPointHolamHaserForVav                   0x05BA
#define U_HebrewPointQubuts                             0x05BB
#define U_HebrewPointDageshOrMapiq                      0x05BC
#define U_HebrewPointMeteg                              0x05BD
#define U_HebrewPunctuationMaqaf                        0x05BE
#define U_HebrewPointRafe                               0x05BF
#define U_HebrewPunctuationPaseq                        0x05C0
#define U_HebrewPointShinDot                            0x05C1
#define U_HebrewPointSinDot                             0x05C2
#define U_HebrewPunctuationSofPasuq                     0x05C3

   /*        Puncta extraordinaria: */
#define U_HebrewMarkUpperDot                            0x05C4
#define U_HebrewMarkLowerDot                            0x05C5

   /*        Points and punctuation: */
#define U_HebrewPunctuationNunHafukha                   0x05C6
#define U_HebrewPointQamatsQatan                        0x05C7

#define U_HebrewLetterAlef                              0x05D0
#define U_HebrewLetterBet                               0x05D1
#define U_HebrewLetterGimel                             0x05D2
#define U_HebrewLetterDalet                             0x05D3
#define U_HebrewLetterHe                                0x05D4
#define U_HebrewLetterVav                               0x05D5
#define U_HebrewLetterZayin                             0x05D6
#define U_HebrewLetterHet                               0x05D7
#define U_HebrewLetterTet                               0x05D8
#define U_HebrewLetterYod                               0x05D9
#define U_HebrewLetterFinalKaf                          0x05DA
#define U_HebrewLetterKaf                               0x05DB
#define U_HebrewLetterLamed                             0x05DC
#define U_HebrewLetterFinalMem                          0x05DD
#define U_HebrewLetterMem                               0x05DE
#define U_HebrewLetterFinalNun                          0x05DF
#define U_HebrewLetterNun                               0x05E0
#define U_HebrewLetterSamekh                            0x05E1
#define U_HebrewLetterAyin                              0x05E2
#define U_HebrewLetterFinalPe                           0x05E3
#define U_HebrewLetterPe                                0x05E4
#define U_HebrewLetterFinalTsadi                        0x05E5
#define U_HebrewLetterTsadi                             0x05E6
#define U_HebrewLetterQof                               0x05E7
#define U_HebrewLetterResh                              0x05E8
#define U_HebrewLetterShin                              0x05E9
#define U_HebrewLetterTav                               0x05EA

   /*        Yiddish digraphs: */
#define U_HebrewLigatureYiddishDoubleVav                0x05F0
#define U_HebrewLigatureYiddishVavYod                   0x05F1
#define U_HebrewLigatureYiddishDoubleYod                0x05F2

   /*        Additional punctuation: */
#define U_HebrewPunctuationGeresh                       0x05F3
#define U_HebrewPunctuationGershayim                    0x05F4


   /* ------ 0600-06FF: Arabic ------ */
   
   /*        Subtending marks: */
#define U_ArabicNumberSign                              0x0600
#define U_ArabicSignSanah                               0x0601
#define U_ArabicFootnoteMarker                          0x0602
#define U_ArabicSignSafha                               0x0603
/* #define U_0604                                       0xFFFF      */
/* #define U_0605                                       0xFFFF      */

   /*        Radix symbols: */
#define U_ArabicIndicCubeRoot                           0x0606
#define U_ArabicIndicFourthRoot                         0x0607

   /*        Letterlike symbol: */
#define U_ArabicRay                                     0x0608

   /*        Punctuation: */
#define U_ArabicIndicPerMilleSign                       0x0609
#define U_ArabicIndicPerTenThousandSign                 0x060A

   /*        Currency sign: */
#define U_AfghaniSign                                   0x060B

   /*        Punctuation: */
#define U_ArabicComma                                   0x060C
#define U_ArabicDateSeparator                           0x060D

   /*        Poetic marks: */
#define U_ArabicPoeticVerseSign                         0x060E
#define U_ArabicSignMisra                               0x060F

   /*        Honorifics: */
#define U_ArabicSignSallallahouAlayheWassallam          0x0610
#define U_ArabicSignAlayheAssallam                      0x0611
#define U_ArabicSignRahmatullahAlayhe                   0x0612
#define U_ArabicSignRadiAllahouAnhu                     0x0613
#define U_ArabicSignTakhallus                           0x0614

   /*        Koranic annotation sign: */
#define U_ArabicSmallHighTah                            0x0615

   /*        Extended Arabic mark: */
#define U_ArabicSmallHighLigatureAlefWithLamWithYeh     0x0616

   /*        Koranic annotation signs: */
#define U_ArabicSmallHighZain                           0x0617
#define U_ArabicSmallFatha                              0x0618
#define U_ArabicSmallDamma                              0x0619
#define U_ArabicSmallKasra                              0x061A

   /*        Punctuation: */
#define U_ArabicSemicolon                               0x061B
/* #define U_061C   <reserved>                          0xFFFF      */
/* #define U_061D   <reserved>                          0xFFFF      */
#define U_ArabicTripleDotPunctuationMark                0x061E
#define U_ArabicQuestionMark                            0x061F

   /*        Based on ISO 8859-6: */
/* #define U_0620   <reserved>                          0xFFFF      */
#define U_ArabicLetterHamza                             0x0621
#define U_ArabicLetterAlefWithMaddaAbove                0x0622
#define U_ArabicLetterAlefWithHamzaAbove                0x0623
#define U_ArabicLetterWawWithHamzaAbove                 0x0624
#define U_ArabicLetterAlefWithHamzaBelow                0x0625
#define U_ArabicLetterYehWithHamzaAbove                 0x0626
#define U_ArabicLetterAlef                              0x0627
#define U_ArabicLetterBeh                               0x0628
#define U_ArabicLetterTehMarbuta                        0x0629
#define U_ArabicLetterTeh                               0x062A
#define U_ArabicLetterTheh                              0x062B
#define U_ArabicLetterJeem                              0x062C
#define U_ArabicLetterHah                               0x062D
#define U_ArabicLetterKhah                              0x062E
#define U_ArabicLetterDal                               0x062F
#define U_ArabicLetterThal                              0x0630
#define U_ArabicLetterReh                               0x0631
#define U_ArabicLetterZain                              0x0632
#define U_ArabicLetterSeen                              0x0633
#define U_ArabicLetterSheen                             0x0634
#define U_ArabicLetterSad                               0x0635
#define U_ArabicLetterDad                               0x0636
#define U_ArabicLetterTah                               0x0637
#define U_ArabicLetterZah                               0x0638
#define U_ArabicLetterAin                               0x0639
#define U_ArabicLetterGhain                             0x063A

   /*        Additions for early Persian and Azerbaijani: */
#define U_ArabicLetterKehehWithTwoDotsAbove             0x063B
#define U_ArabicLetterKehehWithThreeDotsBelow           0x063C
#define U_ArabicLetterFarsiYehWithInvertedV             0x063D
#define U_ArabicLetterFarsiYehWithTwoDotsAbove          0x063E
#define U_ArabicLetterFarsiYehWithThreeDotsAbove        0x063F

   /*        Based on ISO 8859-6: */
#define U_ArabicTatweel                                 0x0640
#define U_ArabicLetterFeh                               0x0641
#define U_ArabicLetterQaf                               0x0642
#define U_ArabicLetterKaf                               0x0643
#define U_ArabicLetterLam                               0x0644
#define U_ArabicLetterMeem                              0x0645
#define U_ArabicLetterNoon                              0x0646
#define U_ArabicLetterHeh                               0x0647
#define U_ArabicLetterWaw                               0x0648
#define U_ArabicLetterAlefMaksura                       0x0649
#define U_ArabicLetterYeh                               0x064A

   /*        Points from ISO 8859-6: */
#define U_ArabicFathatan                                0x064B
#define U_ArabicDammatan                                0x064C
#define U_ArabicKasratan                                0x064D
#define U_ArabicFatha                                   0x064E
#define U_ArabicDamma                                   0x064F
#define U_ArabicKasra                                   0x0650
#define U_ArabicShadda                                  0x0651
#define U_ArabicSukun                                   0x0652

   /*        Combining maddah and hamza: */
#define U_ArabicMaddahAbove                             0x0653
#define U_ArabicHamzaAbove                              0x0654
#define U_ArabicHamzaBelow                              0x0655

   /*        Other combining marks: */
#define U_ArabicSubscriptAlef                           0x0656
#define U_ArabicInvertedDamma                           0x0657
#define U_ArabicMarkNoonGhunna                          0x0658
#define U_ArabicZwarakay                                0x0659
#define U_ArabicVowelSignSmallVAbove                    0x065A
#define U_ArabicVowelSignInvertedSmallVAbove            0x065B
#define U_ArabicVowelSignDotBelow                       0x065C
#define U_ArabicReversedDamma                           0x065D
#define U_ArabicFathaWithTwoDots                        0x065E
/* #define U_065F                                       0xFFFF      */

   /*        Arabic-Indic digits: */
#define U_ArabicIndicDigitZero                          0x0660
#define U_ArabicIndicDigitOne                           0x0661
#define U_ArabicIndicDigitTwo                           0x0662
#define U_ArabicIndicDigitThree                         0x0663
#define U_ArabicIndicDigitFour                          0x0664
#define U_ArabicIndicDigitFive                          0x0665
#define U_ArabicIndicDigitSix                           0x0666
#define U_ArabicIndicDigitSeven                         0x0667
#define U_ArabicIndicDigitEight                         0x0668
#define U_ArabicIndicDigitNine                          0x0669

   /*        Punctuation: */
#define U_ArabicPercentSign                             0x066A
#define U_ArabicDecimalSeparator                        0x066B
#define U_ArabicThousandsSeparator                      0x066C
#define U_ArabicFivePointedStar                         0x066D

   /*        Archaic letters: */
#define U_ArabicLetterDotlessBeh                        0x066E
#define U_ArabicLetterDotlessQaf                        0x066F

   /*        Point: */
#define U_ArabicLetterSuperscriptAlef                   0x0670

   /*        Extended Arabic letters: */
#define U_ArabicLetterAlefWasla                         0x0671
#define U_ArabicLetterAlefWithWavyHamzaAbove            0x0672
#define U_ArabicLetterAlefWithWavyHamzaBelow            0x0673
#define U_ArabicLetterHighHamza                         0x0674
#define U_ArabicLetterHighHamzaAlef                     0x0675
#define U_ArabicLetterHighHamzaWas                      0x0676
#define U_ArabicLetterUWithHamzaAbove                   0x0677
#define U_ArabicLetterHighHamzaYeh                      0x0678
#define U_ArabicLetterTteh                              0x0679
#define U_ArabicLetterTteheh                            0x067A
#define U_ArabicLetterBeeh                              0x067B
#define U_ArabicLetterTehWithRing                       0x067C
#define U_ArabicLetterTehWithThreeDotsAboveDownwards    0x067D
#define U_ArabicLetterPeh                               0x067E
#define U_ArabicLetterTeheh                             0x067F
#define U_ArabicLetterBeheh                             0x0680
#define U_ArabicLetterHahWithHamzaAbove                 0x0681
#define U_ArabicLetterHahWithTwoDotsVerticalAbove       0x0682
#define U_ArabicLetterNyeh                              0x0683
#define U_ArabicLetterDyeh                              0x0684
#define U_ArabicLetterHahWithThreeDotsAbove             0x0685
#define U_ArabicLetterTcheh                             0x0686
#define U_ArabicLetterTcheheh                           0x0687
#define U_ArabicLetterDdal                              0x0688
#define U_ArabicLetterDdalWithRing                      0x0689
#define U_ArabicLetterDalWithDotBelow                   0x068A
#define U_ArabicLetterDalWithDotBelowndSmallTah         0x068B
#define U_ArabicLetterDahal                             0x068C
#define U_ArabicLetterDdahal                            0x068D
#define U_ArabicLetterDul                               0x068E
#define U_ArabicLetterDalWithThreeDotsAboveDownwards    0x068F
#define U_ArabicLetterDalWithFourDotsAbove              0x0690
#define U_ArabicLetterRreh                              0x0691
#define U_ArabicLetterRehWithSmallV                     0x0692
#define U_ArabicLetterRehWithRing                       0x0693
#define U_ArabicLetterRehWithDotBelow                   0x0694
#define U_ArabicLetterRehWithSmallVBelow                0x0695
#define U_ArabicLetterRehWithDotBelowAndDotAbove        0x0696
#define U_ArabicLetterRehWithTwoDotsAbove               0x0697
#define U_ArabicLetterJeh                               0x0698
#define U_ArabicLetterRehWithFourDotsAbove              0x0699
#define U_ArabicLetterSeenWithDotBelowAndDotAbove       0x069A
#define U_ArabicLetterSeenWithThreeDotsBelow            0x069B
#define U_ArabicLetterSeenWithThreeDotsBelowAndThreeDotsAbove    0x069C
#define U_ArabicLetterSadWithTwoDotsBelow               0x069D
#define U_ArabicLetterSadWithThreeDotsAbove             0x069E
#define U_ArabicLetterTahWithThreeDotsAbove             0x069F
#define U_ArabicLetterAinWithThreeDotsAbove             0x06A0
#define U_ArabicLetterDotlessFeh                        0x06A1
#define U_ArabicLetterFehWithDotMovedBelow              0x06A2
#define U_ArabicLetterFehWithDotBelow                   0x06A3
#define U_ArabicLetterVeh                               0x06A4
#define U_ArabicLetterFehWithThreeDotsBelow             0x06A5
#define U_ArabicLetterPeheh                             0x06A6
#define U_ArabicLetterQafWithDotAbove                   0x06A7
#define U_ArabicLetterQafWithThreeDotsAbove             0x06A8
#define U_ArabicLetterKeheh                             0x06A9
#define U_ArabicLetterSwashKaf                          0x06AA
#define U_ArabicLetterKafWithRing                       0x06AB
#define U_ArabicLetterKafWithDotAbove                   0x06AC
#define U_ArabicLetterNg                                0x06AD
#define U_ArabicLetterKafWithThreeDotsBelow             0x06AE
#define U_ArabicLetterGaf                               0x06AF
#define U_ArabicLetterGafWithRing                       0x06B0
#define U_ArabicLetterNgoeh                             0x06B1
#define U_ArabicLetterGafWithTwoDotsBelow               0x06B2
#define U_ArabicLetterGueh                              0x06B3
#define U_ArabicLetterGafWithThreeDotsAbove             0x06B4
#define U_ArabicLetterLamWithSmallV                     0x06B5
#define U_ArabicLetterLamWithDotAbove                   0x06B6
#define U_ArabicLetterLamWithThreeDotsAbove             0x06B7
#define U_ArabicLetterLamWithThreeDotsBelow             0x06B8
#define U_ArabicLetterNoonWithDotBelow                  0x06B9
#define U_ArabicLetterNoonGhunna                        0x06BA
#define U_ArabicLetterRnoon                             0x06BB
#define U_ArabicLetterNoonWithRing                      0x06BC
#define U_ArabicLetterNoonWithThreeDotsAbove            0x06BD
#define U_ArabicLetterHehDoachashmee                    0x06BE
#define U_ArabicLetterTchehWithDotAbove                 0x06BF
#define U_ArabicLetterHehWithYehAbove                   0x06C0
#define U_ArabicLetterHehGoal                           0x06C1
#define U_ArabicLetterHehGoalWithHamzaAbove             0x06C2
#define U_ArabicLetterTehMarbutaGoal                    0x06C3
#define U_ArabicLetterWawWithRing                       0x06C4
#define U_ArabicLetterKirghizOe                         0x06C5
#define U_ArabicLetterOe                                0x06C6
#define U_ArabicLetterU                                 0x06C7
#define U_ArabicLetterYu                                0x06C8
#define U_ArabicLetterKirghizYu                         0x06C9
#define U_ArabicLetterWawWithTwoDotsAbove               0x06CA
#define U_ArabicLetterVe                                0x06CB
#define U_ArabicLetterFarsiYeh                          0x06CC
#define U_ArabicLetterYehWithTail                       0x06CD
#define U_ArabicLetterYehWithSMallV                     0x06CE
#define U_ArabicLetterWawWithDotAbove                   0x06CF
#define U_ArabicLetterE                                 0x06D0
#define U_ArabicLetterYehWithThreeDotsBelow             0x06D1
#define U_ArabicLetterYehBarree                         0x06D2
#define U_ArabicLetterYeeBarreeWithHamzaAbove           0x06D3

   /*        Punctuation: */
#define U_ArabicFullStop                                0x06D4

   /*        Extended Arabic letter: */
#define U_ArabicLetterAe                                0x06D5

   /*        Koranic annotation signs: */
#define U_ArabicSmallHighLigatureSadWithLamWithAlefMaksura   0x06D6
#define U_ArabicSmallHighLigatureQafWithLamWithAlefMaksura   0x06D7
#define U_ArabicSmallHighMeemInitialForm                0x06D8
#define U_ArabicSmallHighLamAlef                        0x06D9
#define U_ArabicSmallHighJeem                           0x06DA
#define U_ArabicSmallHighThreeDots                      0x06DB
#define U_ArabicSmallHighSeen                           0x06DC
#define U_ArabicEndOfAyah                               0x06DD
#define U_ArabicStartOfRubElHizb                        0x06DE
#define U_ArabicSmallHighRoundedZero                    0x06DF
#define U_ArabicSmallHighUprightRectangularZero         0x06E0
#define U_ArabicSmallHighDotlessHeadOfKhah              0x06E1
#define U_ArabicSmallHighMeemIsolatedForm               0x06E2
#define U_ArabicSmallLowSeen                            0x06E3
#define U_ArabicSmallHighMadda                          0x06E4
#define U_ArabicSmallWaw                                0x06E5
#define U_ArabicSmallYeh                                0x06E6
#define U_ArabicSmallHighYeh                            0x06E7
#define U_ArabicSmallHighNoon                           0x06E8
#define U_ArabicPlaceOfSajdah                           0x06E9
#define U_ArabicEmptyCentreLowStop                      0x06EA
#define U_ArabicEmptyCentreHighStop                     0x06EB
#define U_ArabicRoundedHighStopithFilledCentre          0x06EC
#define U_ArabicSmallLowMeem                            0x06ED

   /*        Extended Arabic letters for Parkari: */
#define U_ArabicLetterDalWithInvertedV                  0x06EE
#define U_ArabicLetterRehWithInvertedV                  0x06EF

   /*        Extended Arabic-Indic digits: */
#define U_ExtendedArabicIndicDigitZero                  0x06F0
#define U_ExtendedArabicIndicDigitOne                   0x06F1
#define U_ExtendedArabicIndicDigitTwo                   0x06F2
#define U_ExtendedArabicIndicDigitThree                 0x06F3
#define U_ExtendedArabicIndicDigitFour                  0x06F4
#define U_ExtendedArabicIndicDigitFive                  0x06F5
#define U_ExtendedArabicIndicDigitSix                   0x06F6
#define U_ExtendedArabicIndicDigitSeven                 0x06F7
#define U_ExtendedArabicIndicDigitEight                 0x06F8
#define U_ExtendedArabicIndicDigitNine                  0x06F9

   /*        Extended Arabic letters: */
#define U_ArabicLetterSheenWithDotBelow                 0x06FA
#define U_ArabicLetterDadWithDotBelow                   0x06FB
#define U_ArabicLetterGhainWithDotBelow                 0x06FC

   /*        Signs for Sindhi: */
#define U_ArabicSignSindhiAmpersand                     0x06FD
#define U_ArabicSignSindhiPostpositionMen               0x06FE

   /*        Extended Arabic letter for Parkari: */
#define U_ArabicLetterHehWithInvertedV                  0x06FF


   /* ------ 0700-074F: Syriac ------ */
   /* ------ 0780-07BF: Thaana ------ */
   /* ------ 0900-097F: Devanagari ------ */
   /* ------ 0980-09FF: Bengali ------ */
   /* ------ 0A00-0A7F: Gurmukhi ------ */
   /* ------ 0A80-0AFF: Gujarati ------ */
   /* ------ 0B00-0B7F: Oriya ------ */
   /* ------ 0B80-0BFF: Tamil ------ */
   /* ------ 0C80-0CFF: Kannada ------ */
   /* ------ 0D00-0D7F: Malayalam ------ */
   /* ------ 0D80-0DFF: Sinhala ------ */
   
   
   /* ------ 0E00-0E7F: Thai (based on TIS 620-2533) ------ */

/* #define U_0E00                                       0xFFFF      */

   /*        Consonants: */
#define U_ThaiCharacterKoKai                            0x0E01
#define U_ThaiCharacterKhoKhai                          0x0E02
#define U_ThaiCharacterKhoKhuat                         0x0E03
#define U_ThaiCharacterKhoKhwai                         0x0E04
#define U_ThaiCharacterKhoKhon                          0x0E05
#define U_ThaiCharacterKhoRakhang                       0x0E06
#define U_ThaiCharacterNgoNgu                           0x0E07
#define U_ThaiCharacterChoChan                          0x0E08
#define U_ThaiCharacterChoChing                         0x0E09
#define U_ThaiCharacterChoChang                         0x0E0A
#define U_ThaiCharacterSoSo                             0x0E0B
#define U_ThaiCharacterChoChoe                          0x0E0C
#define U_ThaiCharacterYoYing                           0x0E0D
#define U_ThaiCharacterDoChada                          0x0E0E
#define U_ThaiCharacterToPatak                          0x0E0F
#define U_ThaiCharacterThoThan                          0x0E10
#define U_ThaiCharacterThoNangmontho                    0x0E11
#define U_ThaiCharacterThoPhuthao                       0x0E12
#define U_ThaiCharacterNoNen                            0x0E13
#define U_ThaiCharacterDoDek                            0x0E14
#define U_ThaiCharacterToTao                            0x0E15
#define U_ThaiCharacterThoThung                         0x0E16
#define U_ThaiCharacterThoThahan                        0x0E17
#define U_ThaiCharacterThoThong                         0x0E18
#define U_ThaiCharacterNoNu                             0x0E19
#define U_ThaiCharacterBoBaimai                         0x0E1A
#define U_ThaiCharacterPoPla                            0x0E1B
#define U_ThaiCharacterPhoPhung                         0x0E1C
#define U_ThaiCharacterFoFa                             0x0E1D
#define U_ThaiCharacterPhoPhan                          0x0E1E
#define U_ThaiCharacterFoFan                            0x0E1F
#define U_ThaiCharacterPhoSamphao                       0x0E20
#define U_ThaiCharacterMoMa                             0x0E21
#define U_ThaiCharacterYoYak                            0x0E22
#define U_ThaiCharacterRoRua                            0x0E23
#define U_ThaiCharacterRu                               0x0E24
#define U_ThaiCharacterLoLing                           0x0E25
#define U_ThaiCharacterLu                               0x0E26
#define U_ThaiCharacterWoWaen                           0x0E27
#define U_ThaiCharacterSoSala                           0x0E28
#define U_ThaiCharacterSoRusi                           0x0E29
#define U_ThaiCharacterSoSua                            0x0E2A
#define U_ThaiCharacterHoHip                            0x0E2B
#define U_ThaiCharacterLoChula                          0x0E2C
#define U_ThaiCharacterOAng                             0x0E2D
#define U_ThaiCharacterHoNokhuk                         0x0E2E

   /*        Sign: */
#define U_ThaiCharacterPaiyannoi                        0x0E2F

   /*        Vowels: */
#define U_ThaiCharacterSaraA                            0x0E30
#define U_ThaiCharacterMaiHanAkat                       0x0E31
#define U_ThaiCharacterSaraAa                           0x0E32
#define U_ThaiCharacterSaraAm                           0x0E33
#define U_ThaiCharacterSaraI                            0x0E34
#define U_ThaiCharacterSaraIi                           0x0E35
#define U_ThaiCharacterSaraUe                           0x0E36
#define U_ThaiCharacterSaraUee                          0x0E37
#define U_ThaiCharacterSaraU                            0x0E38
#define U_ThaiCharacterSaraUu                           0x0E39
#define U_ThaiCharacterPhinthu                          0x0E3A
/* #define U_0E3B                                       0x0E3B      */
/* #define U_0E3C                                       0x0E3C      */
/* #define U_0E3D                                       0x0E3D      */
/* #define U_0E3E                                       0x0E3E      */

   /*        Currency symbol: */
#define U_ThaiCurrencySymbolBaht                        0x0E3F

   /*        Vowels: */
#define U_ThaiCharacterSaraE                            0x0E40
#define U_ThaiCharacterSaraAe                           0x0E41
#define U_ThaiCharacterSaraO                            0x0E42
#define U_ThaiCharacterSaraAiMaimuan                    0x0E43
#define U_ThaiCharacterSaraAiMaimalai                   0x0E44

   /*        Vowel length sign: */
#define U_ThaiCharacterLakkhangyao                      0x0E45

   /*        Repetition mark: */
#define U_ThaiCharacterMaiyamok                         0x0E46

   /*        Vowel: */
#define U_ThaiCharacterMaitaikhu                        0x0E47

   /*        Tone marks: */
#define U_ThaiCharacterMaiEk                            0x0E48
#define U_ThaiCharacterMaiTho                           0x0E49
#define U_ThaiCharacterMaiTri                           0x0E4A
#define U_ThaiCharacterMaiChattawa                      0x0E4B

   /*        Signs: */
#define U_ThaiCharacterThanthakhat                      0x0E4C
#define U_ThaiCharacterNikhahit                         0x0E4D
#define U_ThaiCharacterYamakkan                         0x0E4E
#define U_ThaiCharacterFongman                          0x0E4F

   /*        Signs: */
#define U_ThaiDigitZero                                 0x0E50
#define U_ThaiDigitOne                                  0x0E51
#define U_ThaiDigitTwo                                  0x0E52
#define U_ThaiDigitThree                                0x0E53
#define U_ThaiDigitFour                                 0x0E54
#define U_ThaiDigitFive                                 0x0E55
#define U_ThaiDigitSix                                  0x0E56
#define U_ThaiDigitSeven                                0x0E57
#define U_ThaiDigitEight                                0x0E58
#define U_ThaiDigitNine                                 0x0E59

   /*        Signs: */
#define U_ThaiCharacterAngkhankhu                       0x0E5A
#define U_ThaiCharacterKhomut                           0x0E5B
/* 0x0E5C ... 0x0E7F ==  RESERVED */
   
   /* ------ 0E80-0EFF: Lao ------ */
   /* ------ 0F00-0FFF: Tibetan ------ */
   /* ------ 1000-109F: Myanmar ------ */
   /* ------ 10A0-10FF: Georgian ------ */
   /* ------ 1100-11FF: Hangul Jamo ------ */
   /* ------ 1200-137F: Ethiopic ------ */
   /* ------ 13A0-13FF: Cherokee ------ */
   /* ------ 1400-167F: Unified Canadian Aboriginal Syllabics ------ */
   /* ------ 1680-169F: Ogham ------ */
   /* ------ 16A0-16FF: Runic ------ */
   /* ------ 1700-171F: Tagalog ------ */
   /* ------ 1720-173F: Hanunoo ------ */
   /* ------ 1740-175F: Buhid ------ */
   /* ------ 1760-177F: Tagbanwa ------ */
   /* ------ 1780-17FF: Khmer ------ */
   /* ------ 1800-18AF: Mongolian ------ */
   
   
   /* ------ 1E00-1EFF: Latin Extended Additional ------ */
   
   /*        Latin general use extensions: */
#define U_LatinCapitalLetterAWithRingBelow              0x1E00
#define U_LatinSmallLetterAWithRingBelow                0x1E01
#define U_LatinCapitalLetterBWithDotAbove               0x1E02
#define U_LatinSmallLetterBWithDotAbove                 0x1E03
#define U_LatinCapitalLetterBWithDotBelow               0x1E04
#define U_LatinSmallLetterBWithDotBelow                 0x1E05
#define U_LatinCapitalLetterBWithLineBelow              0x1E06
#define U_LatinSmallLetterBWithLineBelow                0x1E07
#define U_LatinCapitalLetterCWithCedillaAndAcute        0x1E08
#define U_LatinSmallLetterCWithCedillaAndAcute          0x1E09
#define U_LatinCapitalLetterDWithDotAbove               0x1E0A
#define U_LatinSmallLetterDWithDotAbove                 0x1E0B
#define U_LatinCapitalLetterDWithDotBelow               0x1E0C
#define U_LatinSmallLetterDWithDotBelow                 0x1E0D
#define U_LatinCapitalLetterDWithLineBelow              0x1E0E
#define U_LatinSmallLetterDWithLineBelow                0x1E0F
#define U_LatinCapitalLetterDWithCedilla                0x1E10
#define U_LatinSmallLetterDWithCedilla                  0x1E11
#define U_LatinCapitalLetterDWithCircumflexBelow        0x1E12
#define U_LatinSmallLetterDWithCircumflexBelow          0x1E13
#define U_LatinCapitalLetterEWithMacronAndGrave         0x1E14
#define U_LatinSmallLetterEWithMacronAndGrave           0x1E15
#define U_LatinCapitalLetterEWithMacronAndAcute         0x1E16
#define U_LatinSmallLetterEWithMacronAndAcute           0x1E17
#define U_LatinCapitalLetterEWithCircumflexBelow        0x1E18
#define U_LatinSmallLetterEWithCircumflexBelow          0x1E19
#define U_LatinCapitalLetterEWithTildeBelow             0x1E1A
#define U_LatinSmallLetterEWithTildeBelow               0x1E1B
#define U_LatinCapitalLetterEWithCedillaAndBreve        0x1E1C
#define U_LatinSmallLetterEWithCedillaAndBreve          0x1E1D
#define U_LatinCapitalLetterFWithDotAbove               0x1E1E
#define U_LatinSmallLetterFWithDotAbove                 0x1E1F
#define U_LatinCapitalLetterGWithMacron                 0x1E20
#define U_LatinSmallLetterGWithMacron                   0x1E21
#define U_LatinCapitalLetterHWithDotAbove               0x1E22
#define U_LatinSmallLetterHWithDotAbove                 0x1E23
#define U_LatinCapitalLetterHWithDotBelow               0x1E24
#define U_LatinSmallLetterHWithDotBelow                 0x1E25
#define U_LatinCapitalLetterHWithDiaeresis              0x1E26
#define U_LatinSmallLetterHWithDiaeresis                0x1E27
#define U_LatinCapitalLetterHWithCedilla                0x1E28
#define U_LatinSmallLetterHWithCedilla                  0x1E29
#define U_LatinCapitalLetterHWithBreveBelow             0x1E2A
#define U_LatinSmallLetterHWithBreveBelow               0x1E2B
#define U_LatinCapitalLetterIWithTildeBelow             0x1E2C
#define U_LatinSmallLetterIWithTildeBelow               0x1E2D
#define U_LatinCapitalLetterIWithDiaeresisAndAcute      0x1E2E
#define U_LatinSmallLetterIWithDiaeresisAndAcute        0x1E2F
#define U_LatinCapitalLetterKWithAcute                  0x1E30
#define U_LatinSmallLetterKWithAcute                    0x1E31
#define U_LatinCapitalLetterKWithDotBelow               0x1E32
#define U_LatinSmallLetterKWithDotBelow                 0x1E33
#define U_LatinCapitalLetterKWithLineBelow              0x1E34
#define U_LatinSmallLetterKWithLineBelow                0x1E35
#define U_LatinCapitalLetterLWithDotBelow               0x1E36
#define U_LatinSmallLetterLWithDotBelow                 0x1E37
#define U_LatinCapitalLetterLWithDotBelowAndMacron      0x1E38
#define U_LatinSmallLetterLWithDotBelowAndMacron        0x1E39
#define U_LatinCapitalLetterLWithLineBelow              0x1E3A
#define U_LatinSmallLetterLWithLineBelow                0x1E3B
#define U_LatinCapitalLetterLWithCircumflexBelow        0x1E3C
#define U_LatinSmallLetterLWithCircumflexBelow          0x1E3D
#define U_LatinCapitalLetterMWithAcute                  0x1E3E
#define U_LatinSmallLetterMWithAcute                    0x1E3F
#define U_LatinCapitalLetterMWithDotAbove               0x1E40
#define U_LatinSmallLetterMWithDotAbove                 0x1E41
#define U_LatinCapitalLetterMWithDotBelow               0x1E42
#define U_LatinSmallLetterMWithDotBelow                 0x1E43
#define U_LatinCapitalLetterNWithDotAbove               0x1E44
#define U_LatinSmallLetterNWithDotAbove                 0x1E45
#define U_LatinCapitalLetterNWithDotBelow               0x1E46
#define U_LatinSmallLetterNWithDotBelow                 0x1E47
#define U_LatinCapitalLetterNWithLineBelow              0x1E48
#define U_LatinSmallLetterNWithLineBelow                0x1E49
#define U_LatinCapitalLetterNWithCircumflexBelow        0x1E4A
#define U_LatinSmallLetterNWithCircumflexBelow          0x1E4B
#define U_LatinCapitalLetterOWithTildeAndAcute          0x1E4C
#define U_LatinSmallLetterOWithTildeAndAcute            0x1E4D
#define U_LatinCapitalLetterOWithTildeAndDiaeresis      0x1E4E
#define U_LatinSmallLetterOWithTildeAndDiaeresis        0x1E4F
#define U_LatinCapitalLetterOWithMacronAndGrave         0x1E50
#define U_LatinSmallLetterOWithMacronAndGrave           0x1E51
#define U_LatinCapitalLetterOWithMacronAndAcute         0x1E52
#define U_LatinSmallLetterOWithMacronAndAcute           0x1E53
#define U_LatinCapitalLetterPWithAcute                  0x1E54
#define U_LatinSmallLetterPWithAcute                    0x1E55
#define U_LatinCapitalLetterPWithDotAbove               0x1E56
#define U_LatinSmallLetterPWithDotAbove                 0x1E57
#define U_LatinCapitalLetterRWithDotAbove               0x1E58
#define U_LatinSmallLetterRWithDotAbove                 0x1E59
#define U_LatinCapitalLetterRWithDotBelow               0x1E5A
#define U_LatinSmallLetterRWithDotBelow                 0x1E5B
#define U_LatinCapitalLetterRWithDotBelowAndMacron      0x1E5C
#define U_LatinSmallLetterRWithDotBelowAndMacron        0x1E5D
#define U_LatinCapitalLetterRWithLineBelow              0x1E5E
#define U_LatinSmallLetterRWithLineBelow                0x1E5F
#define U_LatinCapitalLetterSWithDotAbove               0x1E60
#define U_LatinSmallLetterSWithDotAbove                 0x1E61
#define U_LatinCapitalLetterSWithDotBelow               0x1E62
#define U_LatinSmallLetterSWithDotBelow                 0x1E63
#define U_LatinCapitalLetterSWithAcuteAndDotAbove       0x1E64
#define U_LatinSmallLetterSWithAcuteAndDotAbove         0x1E65
#define U_LatinCapitalLetterSWithCaronAndDotAbove       0x1E66
#define U_LatinSmallLetterSWithCaronAndDotAbove         0x1E67
#define U_LatinCapitalLetterSWithDotBelowAndDotAbove    0x1E68
#define U_LatinSmallLetterSWithDotBelowAndDotAbove      0x1E69
#define U_LatinCapitalLetterTWithDotAbove               0x1E6A
#define U_LatinSmallLetterTWithDotAbove                 0x1E6B
#define U_LatinCapitalLetterTWithDotBelow               0x1E6C
#define U_LatinSmallLetterTWithDotBelow                 0x1E6D
#define U_LatinCapitalLetterTWithLineBelow              0x1E6E
#define U_LatinSmallLetterTWithLineBelow                0x1E6F
#define U_LatinCapitalLetterTWithCircumflexBelow        0x1E70
#define U_LatinSmallLetterTWithCircumflexBelow          0x1E71
#define U_LatinCapitalLetterUWithDiaeresisBelow         0x1E72
#define U_LatinSmallLetterUWithDiaeresisBelow           0x1E73
#define U_LatinCapitalLetterUWithTildeBelow             0x1E74
#define U_LatinSmallLetterUWithTildeBelow               0x1E75
#define U_LatinCapitalLetterUWithCircumflexBelow        0x1E76
#define U_LatinSmallLetterUWithCircumflexBelow          0x1E77
#define U_LatinCapitalLetterUWithTildeAndAcute          0x1E78
#define U_LatinSmallLetterUWithTildeAndAcute            0x1E79
#define U_LatinCapitalLetterUWithMacronAndDiaeresis     0x1E7A
#define U_LatinSmallLetterUWithMacronAndDiaeresis       0x1E7B
#define U_LatinCapitalLetterVWithTilde                  0x1E7C
#define U_LatinSmallLetterVWithTilde                    0x1E7D
#define U_LatinCapitalLetterVWithDotBelow               0x1E7E
#define U_LatinSmallLetterVWithDotBelow                 0x1E7F
#define U_LatinCapitalLetterWWithGrave                  0x1E80
#define U_LatinSmallLetterWWithGrave                    0x1E81
#define U_LatinCapitalLetterWWithAcute                  0x1E82
#define U_LatinSmallLetterWWithAcute                    0x1E83
#define U_LatinCapitalLetterWWithDiaeresis              0x1E84
#define U_LatinSmallLetterWWithDiaeresis                0x1E85
#define U_LatinCapitalLetterWWithDotAbove               0x1E86
#define U_LatinSmallLetterWWithDotAbove                 0x1E87
#define U_LatinCapitalLetterWWithDotBelow               0x1E88
#define U_LatinSmallLetterWWithDotBelow                 0x1E89
#define U_LatinCapitalLetterXWithDotAbove               0x1E8A
#define U_LatinSmallLetterXWithDotAbove                 0x1E8B
#define U_LatinCapitalLetterXWithDiaeresis              0x1E8C
#define U_LatinSmallLetterXWithDiaeresis                0x1E8D
#define U_LatinCapitalLetterYWithDotAbove               0x1E8E
#define U_LatinSmallLetterYWithDotAbove                 0x1E8F
#define U_LatinCapitalLetterZWithCircumflex             0x1E90
#define U_LatinSmallLetterZWithCircumflex               0x1E91
#define U_LatinCapitalLetterZWithDotBelow               0x1E92
#define U_LatinSmallLetterZWithDotBelow                 0x1E93
#define U_LatinCapitalLetterZWithLineBelow              0x1E94
#define U_LatinSmallLetterZWithLineBelow                0x1E95
#define U_LatinSmallLetterHWithLineBelow                0x1E96
#define U_LatinSmallLetterTWithDiaeresis                0x1E97
#define U_LatinSmallLetterWWithRingAbove                0x1E98
#define U_LatinSmallLetterYWithRingAbove                0x1E99
#define U_LatinSmallLetterAWithRightHalfRing            0x1E9A
#define U_LatinSmallLetterLongSWithDotAbove             0x1E9B

   /*        Medievalist additions: */
#define U_LatinSmallLetterLongSWithDiagonalStroke       0x1E9C
#define U_LatinSmallLetterLongSWithHighStroke           0x1E9D

   /*        Addition for German typography: */
#define U_LatinCapitalLetterSharpS                      0x1E9E

   /*        Medievalist addition: */
#define U_LatinSmallLetterDelta                         0x1E9F

   /*        Latin extensions for Vietnamese: */
#define U_LatinCapitalLetterAWithDotBelow               0x1EA0
#define U_LatinSmallLetterAWithDotBelow                 0x1EA1
#define U_LatinCapitalLetterAWithHookAbove              0x1EA2
#define U_LatinSmallLetterAWithHookAbove                0x1EA3
#define U_LatinCapitalLetterAWithCircumflexAndAcute     0x1EA4
#define U_LatinSmallLetterAWithCircumflexAndAcute       0x1EA5
#define U_LatinCapitalLetterAWithCircumflexAndGrave     0x1EA6
#define U_LatinSmallLetterAWithCircumflexAndGrave       0x1EA7
#define U_LatinCapitalLetterAWithCircumflexAndHookAbove 0x1EA8
#define U_LatinSmallLetterAWithCircumflexAndHookAbove   0x1EA9
#define U_LatinCapitalLetterAWithCircumflexAndTilde     0x1EAA
#define U_LatinSmallLetterAWithCircumflexAndTilde       0x1EAB
#define U_LatinCapitalLetterAWithCircumflexAndDotBelow  0x1EAC
#define U_LatinSmallLetterAWithCircumflexAndDotBelow    0x1EAD
#define U_LatinCapitalLetterAWithBreveAndAcute          0x1EAE
#define U_LatinSmallLetterAWithBreveAndAcute            0x1EAF
#define U_LatinCapitalLetterAWithBreveAndGrave          0x1EB0
#define U_LatinSmallLetterAWithBreveAndGrave            0x1EB1
#define U_LatinCapitalLetterAWithBreveAndHookAbove      0x1EB2
#define U_LatinSmallLetterAWithBreveAndHookAbove        0x1EB3
#define U_LatinCapitalLetterAWithBreveAndTilde          0x1EB4
#define U_LatinSmallLetterAWithBreveAndTilde            0x1EB5
#define U_LatinCapitalLetterAWithBreveAndDotBelow       0x1EB6
#define U_LatinSmallLetterAWithBreveAndDotBelow         0x1EB7
#define U_LatinCapitalLetterEWithDotBelow               0x1EB8
#define U_LatinSmallLetterEWithDotBelow                 0x1EB9
#define U_LatinCapitalLetterEWithHookAbove              0x1EBA
#define U_LatinSmallLetterEWithHookAbove                0x1EBB
#define U_LatinCapitalLetterEWithTilde                  0x1EBC
#define U_LatinSmallLetterEWithTilde                    0x1EBD
#define U_LatinCapitalLetterEWithCircumflexAndAcute     0x1EBE
#define U_LatinSmallLetterEWithCircumflexAndAcute       0x1EBF
#define U_LatinCapitalLetterEWithCircumflexAndGrave     0x1EC0
#define U_LatinSmallLetterEWithCircumflexAndGrave       0x1EC1
#define U_LatinCapitalLetterEWithCircumflexAndHookAbove 0x1EC2
#define U_LatinSmallLetterEWithCircumflexAndHookAbove   0x1EC3
#define U_LatinCapitalLetterEWithCircumflexAndTilde     0x1EC4
#define U_LatinSmallLetterEWithCircumflexAndTilde       0x1EC5
#define U_LatinCapitalLetterEWithCircumflexAndDotBelow  0x1EC6
#define U_LatinSmallLetterEWithCircumflexAndDotBelow    0x1EC7
#define U_LatinCapitalLetterIWithHookAbove              0x1EC8
#define U_LatinSmallLetterIWithHookAbove                0x1EC9
#define U_LatinCapitalLetterIWithDotBelow               0x1ECA
#define U_LatinSmallLetterIWithDotBelow                 0x1ECB
#define U_LatinCapitalLetterOWithDotBelow               0x1ECC
#define U_LatinSmallLetterOWithDotBelow                 0x1ECD
#define U_LatinCapitalLetterOWithHookAbove              0x1ECE
#define U_LatinSmallLetterOWithHookAbove                0x1ECF
#define U_LatinCapitalLetterOWithCircumflexAndAcute     0x1ED0
#define U_LatinSmallLetterOWithCircumflexAndAcute       0x1ED1
#define U_LatinCapitalLetterOWithCircumflexAndGrave     0x1ED2
#define U_LatinSmallLetterOWithCircumflexAndGrave       0x1ED3
#define U_LatinCapitalLetterOWithCircumflexAndHookAbove 0x1ED4
#define U_LatinSmallLetterOWithCircumflexAndHookAbove   0x1ED5
#define U_LatinCapitalLetterOWithCircumflexAndTilde     0x1ED6
#define U_LatinSmallLetterOWithCircumflexAndTilde       0x1ED7
#define U_LatinCapitalLetterOWithCircumflexAndDotBelow  0x1ED8
#define U_LatinSmallLetterOWithCircumflexAndDotBelow    0x1ED9
#define U_LatinCapitalLetterOWithHornAndAcute           0x1EDA
#define U_LatinSmallLetterOWithHornAndAcute             0x1EDB
#define U_LatinCapitalLetterOWithHornAndGrave           0x1EDC
#define U_LatinSmallLetterOWithHornAndGrave             0x1EDD
#define U_LatinCapitalLetterOWithHornAndHookAbove       0x1EDE
#define U_LatinSmallLetterOWithHornAndHookAbove         0x1EDF
#define U_LatinCapitalLetterOWithHornAndTilde           0x1EE0
#define U_LatinSmallLetterOWithHornAndTilde             0x1EE1
#define U_LatinCapitalLetterOWithHornAndDotBelow        0x1EE2
#define U_LatinSmallLetterOWithHornAndDotBelow          0x1EE3
#define U_LatinCapitalLetterUWithDotBelow               0x1EE4
#define U_LatinSmallLetterUWithDotBelow                 0x1EE5
#define U_LatinCapitalLetterUWithHookAbove              0x1EE6
#define U_LatinSmallLetterUWithHookAbove                0x1EE7
#define U_LatinCapitalLetterUWithHornAndAcute           0x1EE8
#define U_LatinSmallLetterUWithHornAndAcute             0x1EE9
#define U_LatinCapitalLetterUWithHornAndGrave           0x1EEA
#define U_LatinSmallLetterUWithHornAndGrave             0x1EEB
#define U_LatinCapitalLetterUWithHornAndHookAbove       0x1EEC
#define U_LatinSmallLetterUWithHornAndHookAbove         0x1EED
#define U_LatinCapitalLetterUWithHornAndTilde           0x1EEE
#define U_LatinSmallLetterUWithHornAndTilde             0x1EEF
#define U_LatinCapitalLetterUWithHornAndDotBelow        0x1EF0
#define U_LatinSmallLetterUWithHornAndDotBelow          0x1EF1

   /*        Latin general extensions: */
#define U_LatinCapitalLetterYWithGrave                  0x1EF2
#define U_LatinSmallLetterYWithGrave                    0x1EF3
#define U_LatinCapitalLetterYWithDotBelow               0x1EF4
#define U_LatinSmallLetterYWithDotBelow                 0x1EF5
#define U_LatinCapitalLetterYWithHookAbove              0x1EF6
#define U_LatinSmallLetterYWithHookAbove                0x1EF7
#define U_LatinCapitalLetterYWithTilde                  0x1EF8
#define U_LatinSmallLetterYWithTilde                    0x1EF9

   /*        Medievalist additions: */
#define U_LatinCapitalLetterMiddleWelshLL               0x1EFA
#define U_LatinSmallLetterMiddleWelshLL                 0x1EFB
#define U_LatinCapitalLetterMiddleWelshV                0x1EFC
#define U_LatinSmallLetterMiddleWelshV                  0x1EFD
#define U_LatinCapitalLetterYWithLoop                   0x1EFE
#define U_LatinSmallLetterYWithLoop                     0x1EFF

   
   /* ------ 1F00-1FFF: Greek Extended ------ */


   /* ------ 2000-206F: General Punctuation ------ */

   /*        Spaces: */
#define U_EnQuad                                        0x2000  /*  */
#define U_EmQuad                                        0x2001  /*  */
#define U_EnSpace                                       0x2002  /*  */
#define U_EmSpace                                       0x2003  /*  */
#define U_ThreePerEmSpace                               0x2004  /*  */
#define U_FourPerEmSpace                                0x2005  /*  */
#define U_SixPerEmSpace                                 0x2006  /*  */
#define U_FigureSpace                                   0x2007  /*  */
#define U_PunctuationSpace                              0x2008  /*  */
#define U_ThinSpace                                     0x2009  /*  */
#define U_HairSpace                                     0x200A  /*  */
#define U_ZeroWidthSpace                                0x200B  /*  */

   /*        Formatting characters: */
#define U_ZeroWidthNonJoiner                            0x200C  /*  */
#define U_ZeroWidthJoiner                               0x200D  /*  */
#define U_LeftToRightMark                               0x200E  /*  */
#define U_RightToLeftMark                               0x200F  /*  */

   /*        Dashes: */
#define U_Hyphen                                        0x2010  /*  */
#define U_NonBreakingHyphen                             0x2011  /*  */
#define U_FigureDash                                    0x2012  /*  */
#define U_EnDash                                        0x2013  /*  */
#define U_EmDash                                        0x2014  /*  */
#define U_HorizontalBar                                 0x2015  /*  */

   /*        General punctuation: */
#define U_DoubleVerticalLine                            0x2016  /*  */
#define U_DoubleLowLine                                 0x2017  /*  */
#define U_LeftSingleQuotationMark                       0x2018  /*  */
#define U_RightSingleQuotationMark                      0x2019  /*  */
#define U_SingleLow9QuotationMark                       0x201A  /*  */
#define U_SingleHighReversed9QuotationMark              0x201B  /*  */
#define U_LeftDoubleQuotationMark                       0x201C  /*  */
#define U_RightDoubleQuotationMark                      0x201D  /*  */
#define U_DoubleLow9QuotationMark                       0x201E  /*  */
#define U_DoubleHighReversed9QuotationMark              0x201F  /*  */
#define U_Dagger                                        0x2020  /*  */
#define U_DoubleDagger                                  0x2021  /*  */
#define U_Bullet                                        0x2022  /*  */
#define U_TriangularBullet                              0x2023  /*  */
#define U_OneDotLeader                                  0x2024  /*  */
#define U_TwoDotLeader                                  0x2025  /*  */
#define U_HorizontalEllipsis                            0x2026  /*  */
#define U_HyphenationPoint                              0x2027  /*  */

   /*        Formatting characters: */
#define U_LineSeparator                                 0x2028  /*  */
#define U_ParagraphSeparator                            0x2029  /*  */
#define U_LeftToRightEmbedding                          0x202A  /*  */
#define U_RightToLeftEmbedding                          0x202B  /*  */
#define U_PopDirectionalFormatting                      0x202C  /*  */
#define U_LeftToRightOverride                           0x202D  /*  */
#define U_RightToLeftOverride                           0x202E  /*  */
#define U_NarrowNoBreakSpace                            0x202F  /*  */

   /*        General punctuation: */
#define U_PerMilleSign                                  0x2030  /*  */
#define U_PerTenThousandSign                            0x2031  /*  */
#define U_Prime                                         0x2032  /*  */
#define U_DoublePrime                                   0x2033  /*  */
#define U_TriplePrime                                   0x2034  /*  */
#define U_ReversedPrime                                 0x2035  /*  */
#define U_ReversedDoublePrime                           0x2036  /*  */
#define U_ReversedTriplePrime                           0x2037  /*  */
#define U_Caret                                         0x2038  /*  */
#define U_LeftPointingSingleGuillemet                   0x2039  /*  */
#define U_RightPointingSingleGuillemet                  0x203A  /*  */
#define U_ReferenceMark                                 0x203B  /*  */
#define U_DoubleExclamationMark                         0x203C  /*  */
#define U_Interrobang                                   0x203D  /*  */
#define U_Overline                                      0x203E  /*  */
#define U_Undertie                                      0x203F  /*  */
#define U_CharacterTie                                  0x2040  /*  */
#define U_CaretInsertionPoint                           0x2041  /*  */
#define U_Asterism                                      0x2042  /*  */
#define U_HyphenBullet                                  0x2043  /*  */
#define U_FractionSlash                                 0x2044  /*  */
#define U_LeftSquareBracketWithQuill                    0x2045  /*  */
#define U_RightSquareBracketWithQuill                   0x2046  /*  */

   /*        Double punctuation for vertical text: */
#define U_DoubleQuestionMark                            0x2047  /*  */
#define U_QuestionExclamationMark                       0x2048  /*  */
#define U_ExclamationQuestionMark                       0x2049  /*  */

   /*        General punctuation: */
#define U_TironianSignEt                                0x204A  /*  */
#define U_ReversedPilcrowSign                           0x204B  /*  */
#define U_BlackLeftwardsBullet                          0x204C  /*  */
#define U_BlackRightwardsBullet                         0x204D  /*  */
#define U_LowAsterisk                                   0x204E  /*  */
#define U_ReversedSemicolon                             0x204F  /*  */
#define U_CloseUp                                       0x2050  /*  */
#define U_TwoAsterisksAlignedVertically                 0x2051  /*  */
#define U_CommercialMinusSign                           0x2052  /*  */
/* #define U_2053                                       0xFFFF      */
/* #define U_2054                                       0xFFFF      */
/* #define U_2055                                       0xFFFF      */
/* #define U_2056                                       0xFFFF      */
#define U_QuadruplePrime                                0x2057  /*  */
/* #define U_2058                                       0xFFFF      */
/* #define U_2059                                       0xFFFF      */
/* #define U_205A                                       0xFFFF      */
/* #define U_205B                                       0xFFFF      */
/* #define U_205C                                       0xFFFF      */
/* #define U_205D                                       0xFFFF      */
/* #define U_205E                                       0xFFFF      */

   /*        Space: */
#define U_MediumMathematicalSpace                       0x205F  /*  */

   /*        Formatting character: */
#define U_WordJoiner                                    0x2060  /*  */

   /*        Invisible operators: */
#define U_FunctionApplication                           0x2061  /*  */
#define U_InvisibleTimes                                0x2062  /*  */
#define U_InvisibleOperator                             0x2063  /*  */
/* #define U_2064                                       0xFFFF      */
/* #define U_2065                                       0xFFFF      */
/* #define U_2066                                       0xFFFF      */
/* #define U_2067                                       0xFFFF      */
/* #define U_2068                                       0xFFFF      */
/* #define U_2069                                       0xFFFF      */

   /*        Deprecated: */
#define U_InhibitSymmetricSwapping                      0x206A  /*  */
#define U_ActivateSymmetricSwapping                     0x206B  /*  */
#define U_InhibitArabicFormShaping                      0x206C  /*  */
#define U_ActivateArabicFormShaping                     0x206D  /*  */
#define U_NationalDigitShapes                           0x206E  /*  */
#define U_NominalDigitShapes                            0x206F  /*  */

   /* ------ 2070-209F: Superscripts and Subscripts ------ */


#define U_SuperscriptLatinSmallLetterN                  0x207F  /*  */

   /* ------ 20A0-20CF: Currency Symbols ------ */

#define U_EuroCurrencySign                              0x20A0  /* This is NOT the Euro Sign (-> 0x20AC) !! */
#define U_ColonSign                                     0x20A1  /*  */
#define U_CruzeroSign                                   0x20A2  /*  */
#define U_FrenchFrancSign                               0x20A3  /*  */
#define U_LiraSign                                      0x20A4  /*  */
#define U_MillSign                                      0x20A5  /*  */
#define U_NairaSign                                     0x20A6  /*  */
#define U_PesetaSign                                    0x20A7  /*  */
#define U_RupeeSign                                     0x20A8  /*  */
#define U_WonSign                                       0x20A9  /*  */
#define U_NewShequelSign                                0x20AA  /*  */
#define U_DongSign                                      0x20AB  /*  */
#define U_EuroSign                                      0x20AC  /*  */
#define U_KipSign                                       0x20AD  /*  */
#define U_TugrikSign                                    0x20AE  /*  */
#define U_DrachmaSign                                   0x20AF  /*  */
#define U_GermanPennySign                               0x20B0  /*  */
#define U_PesoSign                                      0x20B1  /*  */

   /* ------ 20D0-20FF: Combining Diacritical Marks for Symbols ------ */

   /* ------ 2100-214F: Letterlike Symbols ------ */

   /*        Letterlike symbols: */
#define U_AccountOf                                     0x2100
#define U_AddressedToTheSubject                         0x2101
#define U_DoubleStruckCapitalC                          0x2102
#define U_DegreeCelsius                                 0x2103
#define U_CentreLineSymbol                              0x2104
#define U_CareOf                                        0x2105
#define U_CadaUna                                       0x2106
#define U_EulerConstant                                 0x2107
#define U_Scruple                                       0x2108
#define U_DegreeFahrenheit                              0x2109
#define U_ScriptSmallG                                  0x210A
#define U_ScriptCapitalH                                0x210B
#define U_BlackLetterCapitalH                           0x210C
#define U_DoubleStruckCapitalH                          0x210D
#define U_PlanckConstant                                0x210E
#define U_PlanckConstantOverTwoPi                       0x210F
#define U_ScriptCapitalI                                0x2110
#define U_BlackLetterCapitalI                           0x2111
#define U_ScriptCapitalL                                0x2112
#define U_ScriptSmallL                                  0x2113
#define U_LBBarSymbol                                   0x2114
#define U_DoubleStruckCapitalN                          0x2115
#define U_NumeroSign                                    0x2116
#define U_SoundRecordingCopyright                       0x2117
#define U_ScriptCapitalP                                0x2118
#define U_DoubleStruckCapitalP                          0x2119
#define U_DoubleStruckCapitalQ                          0x211A
#define U_ScriptCapitalR                                0x211B
#define U_BlackLetterCapitalR                           0x211C
#define U_DoubleStruckCapitalR                          0x211D
#define U_PrescriptionTake                              0x211E
#define U_Response                                      0x211F
#define U_ServiceMark                                   0x2120
#define U_TelephoneSign                                 0x2121
#define U_TradeMarkSign                                 0x2122
#define U_Versicle                                      0x2123
#define U_DoubleStruckCapitalZ                          0x2124
#define U_OunceSign                                     0x2125
#define U_OhmSign                                       0x2126
#define U_InvertedOhmSign                               0x2127
#define U_BlackLetterCapitalZ                           0x2128
#define U_TurnedGreekSmallLetterIota                    0x2129
#define U_KelvinSign                                    0x212A
#define U_AngstromSign                                  0x212B
#define U_ScriptCapitalB                                0x212C
#define U_BlackLetterCapitalC                           0x212D
#define U_EstimatedSymbol                               0x212E
#define U_ScriptSmallE                                  0x212F
#define U_ScriptCapitalE                                0x2130
#define U_ScriptCapitalF                                0x2131
#define U_TurnedCapitalF                                0x2132
#define U_ScriptCapitalM                                0x2133
#define U_ScriptSmallO                                  0x2134

   /*        Hebrew letterlike math symbols (left-to-right): */
#define U_AlefSymbol                                    0x2135
#define U_BethSymbol                                    0x2136
#define U_GimelSymbol                                   0x2137
#define U_DaletSymbol                                   0x2138

   /*        Additional letterlike symbols: */
#define U_InformationSource                             0x2139
#define U_RotatedCapitalQ                               0x213A
#define U_213B                                          0x213B
#define U_213C                                          0x213C
#define U_DoubleStruckSmallGamma                        0x213D
#define U_DoubleStruckCapitalGamma                      0x213E
#define U_DoubleStruckCapitalPi                         0x213F

   /*        Double-struck large operator: */
#define U_DoubleStruckNArysummation                     0x2140

   /*        Additional letterlike symbols: */
#define U_TurnedSansSerifCapitalG                       0x2141
#define U_TurnedSansSerifCapitalL                       0x2142
#define U_ReversedSansSerifCapitalL                     0x2143
#define U_TurnedSansSerifCapitalY                       0x2144

   /*        Double-struck italic mathematical symbols: */
#define U_DoubleStruckItalicCapitalD                    0x2145
#define U_DoubleStruckItalicSmallD                      0x2146
#define U_DoubleStruckItalicSmallE                      0x2147
#define U_DoubleStruckItalicSmallI                      0x2148
#define U_DoubleStruckItalicSmallJ                      0x2149

   /*        Additional letterlike symbols: */
#define U_PropertyLine                                  0x214A
#define U_TurnedAmpersand                               0x214B
#define U_214C                                          0x214C
#define U_214D                                          0x214D
#define U_214E                                          0x214E
#define U_214F                                          0x214F


   /* ------ 2150-218F: Number Forms ------ */
   /* ------ 2190-21FF: Arrows ------ */

   /* ------ 2200-22FF: Mathematical Operators ------ */

   /*        N.B.: Not all definitions listed yet!!! */
#define U_ForAll                                        0x2200
#define U_Complement                                    0x2201
#define U_PartialDifferential                           0x2202
#define U_ThereExists                                   0x2203
#define U_ThereDoesNotExist                             0x2204
#define U_EmptySet                                      0x2205
#define U_Increment                                     0x2206
#define U_Nabla                                         0x2207
#define U_ElementOf                                     0x2208
#define U_NotAnElementOf                                0x2209
#define U_SmallElementOf                                0x220A
#define U_ContainsAsMember                              0x220B
#define U_DoesNotContainAsMember                        0x220C
#define U_SmallContainsAsMember                         0x220D
#define U_EndOfProof                                    0x220E
#define U_NAryProduct                                   0x220F
#define U_NAryCoproduct                                 0x2210
#define U_NArySummation                                 0x2211
#define U_MinusSign                                     0x2212
#define U_MinusOrPlusSign                               0x2213
#define U_DivisionSlash                                 0x2215
#define U_SetMinus                                      0x2216
#define U_AsteriskOperator                              0x2217
#define U_RingOperator                                  0x2218
#define U_BulletOperator                                0x2219
#define U_SquareRoot                                    0x221A
#define U_CubeRoot                                      0x221B
#define U_FourthRoot                                    0x221C
#define U_ProportionalTo                                0x221D
#define U_Infinity                                      0x221E
#define U_RightAngle                                    0x221F
#define U_Angle                                         0x2220
#define U_MeasuredAngle                                 0x2221
#define U_SphericalAngle                                0x2222
#define U_Divides                                       0x2223
#define U_DoesNotDivide                                 0x2224
#define U_ParallelTo                                    0x2225
#define U_NotParallelTo                                 0x2226
#define U_LogicalAnd                                    0x2227
#define U_LogicalOr                                     0x2228
#define U_Intersection                                  0x2229
#define U_Union                                         0x222A
#define U_Integral                                      0x222B
#define U_DoubleIntegral                                0x222C
#define U_TripleIntegral                                0x222D
#define U_ContourIntegral                               0x222E
#define U_SurfaceIntegral                               0x222F
   /* ... */                                         /* 0x2230 .. 0x2247 */
#define U_AlmostEqualTo                                 0x2248
   /* ... */                                         /* 0x2249 .. 0x225f */
#define U_NotEqualTo                                    0x2260
#define U_IdenticalTo                                   0x2261
   /* ... */                                         /* 0x2262 .. 0x2263 */
#define U_LessThanOrEqualTo                             0x2264
#define U_GreaterThanOrEqualTo                          0x2265


   /* ------ 2300-23FF: Miscellaneous Technical ------ */

   /* ... */                                         /* 0x2300 .. 0x230F */
#define U_ReversedNotSign                               0x2310
   /* ... */                                         /* 0x2311 .. 0x231F */
#define U_TopHalfIntegral                               0x2320
#define U_BottomHalfIntegral                            0x2321
#define U_Frown                                         0x2322
#define U_Smile                                         0x2323


   /* ------ 2400-243F: Control Pictures ------ */
   /* ------ 2440-245F: Optical Character Recognition ------ */
   /* ------ 2460-24FF: Enclosed Alphanumerics ------ */
   /* ------ 2500-257F: Box Drawing ------ */

#define U_BoxDrawingsLightHorizontal                    0x2500
#define U_BoxDrawingsHeavyHorizontal                    0x2501
#define U_BoxDrawingsLightVertical                      0x2502
#define U_BoxDrawingsHeavyVertical                      0x2503
#define U_BoxDrawingsLightTripleDashHorizontal          0x2504
#define U_BoxDrawingsHeavyTripleDashHorizontal          0x2505
#define U_BoxDrawingsLightTripleDashVertical            0x2506
#define U_BoxDrawingsHeavyTripleDashVertical            0x2507
#define U_BoxDrawingsLightQuadrupleDashHorizontal       0x2508
#define U_BoxDrawingsHeavyQuadrupleDashHorizontal       0x2509
#define U_BoxDrawingsLightQuadrupleDashVertical         0x250A
#define U_BoxDrawingsHeavyQuadrupleDashVertical         0x250B
#define U_BoxDrawingsLightDownAndRight                  0x250C
#define U_BoxDrawingsDownLightAndRightHeavy             0x250D
#define U_BoxDrawingsDownHeavyAndRightLight             0x250E
#define U_BoxDrawingsHeavyDownAndRight                  0x250F
#define U_BoxDrawingsLightDownAndLeft                   0x2510
#define U_BoxDrawingsDownLightAndLeftHeavy              0x2511
#define U_BoxDrawingsDownHeavyAndLeftLight              0x2512
#define U_BoxDrawingsHeavyDownAndLeft                   0x2513
#define U_BoxDrawingsLightUpAndRight                    0x2514
#define U_BoxDrawingsUpLightAndRightHeavy               0x2515
#define U_BoxDrawingsUpHeavyAndRightLight               0x2516
#define U_BoxDrawingsHeavyUpAndRight                    0x2517
#define U_BoxDrawingsLightUpAndLeft                     0x2518
#define U_BoxDrawingsUpLightAndLeftHeavy                0x2519
#define U_BoxDrawingsUpHeavyAndLeftLight                0x251A
#define U_BoxDrawingsHeavyUpAndLeft                     0x251B
#define U_BoxDrawingsLightVerticalAndRight              0x251C
#define U_BoxDrawingsVerticalLightAndRightHeavy         0x251D
#define U_BoxDrawingsUpHeavyAndRightDownLight           0x251E
#define U_BoxDrawingsDownHeavyAndRightUpLight           0x251F
#define U_BoxDrawingsVerticalHeavyAndRightLight         0x2520
#define U_BoxDrawingsDownLightAndRightUpHeavy           0x2521
#define U_BoxDrawingsUpLightAndRightDownHeavy           0x2522
#define U_BoxDrawingsHeavyVerticalAndRight              0x2523
#define U_BoxDrawingsLightVerticalAndLeft               0x2524
#define U_BoxDrawingsVerticalLightAndLeftHeavy          0x2525
#define U_BoxDrawingsUpHeavyAndLeftDownLight            0x2526
#define U_BoxDrawingsDownHeavyAndLeftUpLight            0x2527
#define U_BoxDrawingsVerticalHeavyAndLeftLight          0x2528
#define U_BoxDrawingsDownLightAndLeftUpHeavy            0x2529
#define U_BoxDrawingsUpLightAndLeftDownHeavy            0x252A
#define U_BoxDrawingsHeavyVerticalAndLeft               0x252B
#define U_BoxDrawingsLightDownAndHorizontal             0x252C
#define U_BoxDrawingsLeftHeavyAndRightDownLight         0x252D
#define U_BoxDrawingsRightHeavyAndLeftDownLight         0x252E
#define U_BoxDrawingsDownLightAndHorizontalHeavy        0x252F
#define U_BoxDrawingsDownHeavyAndHorizontalLight        0x2530
#define U_BoxDrawingsRightLightAndLeftDownHeavy         0x2531
#define U_BoxDrawingsLeftLightAndRightDownHeavy         0x2532
#define U_BoxDrawingsHeavyDownAndHorizontal             0x2533
#define U_BoxDrawingsLightUpAndHorizontal               0x2534
#define U_BoxDrawingsLeftHeavyAndRightUpLight           0x2535
#define U_BoxDrawingsRightHeavyAndLeftUpLight           0x2536
#define U_BoxDrawingsUpLightAndHorizontalHeavy          0x2537
#define U_BoxDrawingsUpHeavyAndHorizontalLight          0x2538
#define U_BoxDrawingsRightLightAndLeftUpHeavy           0x2539
#define U_BoxDrawingsLeftLightAndRightUpHeavy           0x253A
#define U_BoxDrawingsHeavyUpAndHorizontal               0x253B
#define U_BoxDrawingsLightVerticalAndHorizontal         0x253C
#define U_BoxDrawingsLeftHeavyAndRightVerticalLight     0x253D
#define U_BoxDrawingsRightHeavyAndLeftVerticalLight     0x253E
#define U_BoxDrawingsVerticalLightAndHorizontalHeavy    0x253F
#define U_BoxDrawingsUpHeavyAndDownHorizontalLight      0x2540
#define U_BoxDrawingsDownHeavyAndUpHorizontalLight      0x2541
#define U_BoxDrawingsVerticalHeavyAndHorizontalLight    0x2542
#define U_BoxDrawingsLeftUpHeavyAndRightDownLight       0x2543
#define U_BoxDrawingsRightUpHeavyAndLeftDownLight       0x2544
#define U_BoxDrawingsLeftDownHeavyAndRightUpLight       0x2545
#define U_BoxDrawingsRightDownHeavyAndLeftUpLight       0x2546
#define U_BoxDrawingsDownLightAndUpHorizontalHeavy      0x2547
#define U_BoxDrawingsUpLightAndDownHorizontalHeavy      0x2548
#define U_BoxDrawingsRightLightAndLeftVerticalHeavy     0x2549
#define U_BoxDrawingsLeftLightAndRightVerticalHeavy     0x254A
#define U_BoxDrawingsHeavyVerticalAndHorizontal         0x254B
#define U_BoxDrawingsLightDoubleDashHorizontal          0x254C
#define U_BoxDrawingsHeavyDoubleDashHorizontal          0x254D
#define U_BoxDrawingsLightDoubleDashVertical            0x254E
#define U_BoxDrawingsHeavyDoubleDashVertical            0x254F
#define U_BoxDrawingsDoubleHorizontal                   0x2550
#define U_BoxDrawingsDoubleVertical                     0x2551
#define U_BoxDrawingsDownSingleAndRightDouble           0x2552
#define U_BoxDrawingsDownDoubleAndRightSingle           0x2553
#define U_BoxDrawingsDoubleDownAndRight                 0x2554
#define U_BoxDrawingsDownSingleAndLeftDouble            0x2555
#define U_BoxDrawingsDownDoubleAndLeftSingle            0x2556
#define U_BoxDrawingsDoubleDownAndLeft                  0x2557
#define U_BoxDrawingsUpSingleAndRightDouble             0x2558
#define U_BoxDrawingsUpDoubleAndRightSingle             0x2559
#define U_BoxDrawingsDoubleUpAndRight                   0x255A
#define U_BoxDrawingsUpSingleAndLeftDouble              0x255B
#define U_BoxDrawingsUpDoubleAndLeftSingle              0x255C
#define U_BoxDrawingsDoubleUpAndLeft                    0x255D
#define U_BoxDrawingsVerticalSingleAndRightDouble       0x255E
#define U_BoxDrawingsVerticalDoubleAndRightSingle       0x255F
#define U_BoxDrawingsDoubleVerticalAndRight             0x2560
#define U_BoxDrawingsVerticalSingleAndLeftDouble        0x2561
#define U_BoxDrawingsVerticalDoubleAndLeftSingle        0x2562
#define U_BoxDrawingsDoubleVerticalAndLeft              0x2563
#define U_BoxDrawingsDownSingleAndHorizontalDouble      0x2564
#define U_BoxDrawingsDownDoubleAndHorizontalSingle      0x2565
#define U_BoxDrawingsDoubleDownAndHorizontal            0x2566
#define U_BoxDrawingsUpSingleAndHorizontalDouble        0x2567
#define U_BoxDrawingsUpDoubleAndHorizontalSingle        0x2568
#define U_BoxDrawingsDoubleUpAndHorizontal              0x2569
#define U_BoxDrawingsVerticalSingleAndHorizontalDouble  0x256A
#define U_BoxDrawingsVerticalDoubleAndHorizontalSingle  0x256B
#define U_BoxDrawingsDoubleVerticalAndHorizontal        0x256C
#define U_BoxDrawingsLightArcDownAndRight               0x256D
#define U_BoxDrawingsLightArcDownAndLeft                0x256E
#define U_BoxDrawingsLightArcUpAndLeft                  0x256F
#define U_BoxDrawingsLightArcUpAndRight                 0x2570
#define U_BoxDrawingsLightDiagonalUpperRightToLowerLeft 0x2571
#define U_BoxDrawingsLightDiagonalUpperLeftToLowerRight 0x2572
#define U_BoxDrawingsLightDiagonalCross                 0x2573
#define U_BoxDrawingsLightLeft                          0x2574
#define U_BoxDrawingsLightUp                            0x2575
#define U_BoxDrawingsLightRight                         0x2576
#define U_BoxDrawingsLightDown                          0x2577
#define U_BoxDrawingsHeavyLeft                          0x2578
#define U_BoxDrawingsHeavyUp                            0x2579
#define U_BoxDrawingsHeavyRight                         0x257A
#define U_BoxDrawingsHeavyDown                          0x257B
#define U_BoxDrawingsLightLeftAndHeavyRight             0x257C
#define U_BoxDrawingsLightUpAndHeavyDown                0x257D
#define U_BoxDrawingsHeavyLeftAndLightRight             0x257E
#define U_BoxDrawingsHeavyUpAndLightDown                0x257F


   /* ------ 2580-259F: Block Elements ------ */

#define U_UpperHalfBlock                                0x2580
#define U_LowerOneEighthBlock                           0x2581
#define U_LowerOneQuarterBlock                          0x2582
#define U_LowerThreeEighthsBlock                        0x2583
#define U_LowerHalfBlock                                0x2584
#define U_LowerFiveEighthsBlock                         0x2585
#define U_LowerThreeQuartersBlock                       0x2586
#define U_LoverSevenEighthsBlock                        0x2587
#define U_FullBlock                                     0x2588
#define U_LeftSevenEighthsBlock                         0x2589
#define U_LeftThreeQuartersBlock                        0x258A
#define U_LeftFiveEighthsBlock                          0x258B
#define U_LeftHalfBlock                                 0x258C
#define U_LeftThreeEighthsBlock                         0x258D
#define U_LeftOneQuarterBlock                           0x258E
#define U_LeftOneEighthBlock                            0x258F
#define U_RightHalfBlock                                0x2590
#define U_LightShade                                    0x2591
#define U_MediumShade                                   0x2592
#define U_DarkShade                                     0x2593
#define U_UpperOneEighthBlock                           0x2594
#define U_rightOneEighthBlock                           0x2595
#define U_QuadrantLowerLeft                             0x2596
#define U_QuadrantLowerRight                            0x2597
#define U_QuadrantUpperLeft                             0x2598
#define U_QuadrantUpperLeftAndLowerLeftAndLowerRight    0x2599
#define U_QuadrantUpperLeftAndLowerRight                0x259A
#define U_QuadrantUpperLeftAndUpperRightAndLowerLeft    0x259B
#define U_QuadrantUpperLeftAndUpperRightAndLowerRight   0x259C
#define U_QuadrantUpperRight                            0x259D
#define U_QuadrantUpperRightAndLowerLeft                0x259E
#define U_QuadrantUpperRightAndLowerLeftAndLowerRight   0x259F


   /* ------ 25A0-25FF: Geometric Shapes ------ */
#define U_BlackSquare                                   0x25A0
#define U_WhiteSquare                                   0x25A1
#define U_WhiteSquareWithRoundedCorners                 0x25A2
#define U_WhiteSquareContainingBlackSmallSquare         0x25A3
#define U_SquareWithHorizontalFill                      0x25A4
#define U_SquareWithVerticalFill                        0x25A5
#define U_SquareWithOrthogonalCrosshatchFill            0x25A6
#define U_SquareWithUpperLeftToLowerRightFill           0x25A7
#define U_SquareWithUpperRightToLowerLeftFill           0x25A8
#define U_SquareWithDiagonaCrosshatchFill               0x25A9
#define U_BlackSmallSquare                              0x25AA
#define U_WhiteSmallSquare                              0x25AB
#define U_BlackRectangle                                0x25AC
#define U_WhiteRectangle                                0x25AD
#define U_BlackVerticalRectangle                        0x25AE
#define U_WhiteVerticalRectangle                        0x25AF
#define U_BlackParallelogram                            0x25B0
#define U_WhiteParallelogram                            0x25B1
#define U_BlackUpPointingTriangle                       0x25B2
#define U_WhiteUpPointingTriangle                       0x25B3
#define U_BlackUpPointingSmallTriangle                  0x25B4
#define U_WhiteUpPointingSmallTriangle                  0x25B5
#define U_BlackRightPointingTriangle                    0x25B6
#define U_WhiteRightPointingTriangle                    0x25B7
#define U_BlackRightPointingSmallTriangle               0x25B8
#define U_BlackWhitePointingSmallTriangle               0x25B9
#define U_BlackRightPointingPointer                     0x25BA
#define U_WhiteRightPointingPointer                     0x25BB
#define U_BlackDownPointingTriangle                     0x25BC
#define U_WhiteDownPointingTriangle                     0x25BD
#define U_BlackDownPointingSmallTriangle                0x25BE
#define U_WhiteDownPointingSmallTriangle                0x25BF
#define U_BlackLeftPointingTriangle                     0x25C0
#define U_WhiteLeftPointingTriangle                     0x25C1
#define U_BlackLeftPointingSmallTriangle                0x25C2
#define U_WhiteLeftPointingSmallTriangle                0x25C3
#define U_BlackLeftPointingPointer                      0x25C4
#define U_WhiteLeftPointingPointer                      0x25C5
#define U_BlackDiamond                                  0x25C6
#define U_WhiteDiamond                                  0x25C7
#define U_WhiteDiamondContainingBlackSmallDiamond       0x25C8
#define U_Fisheye                                       0x25C9
#define U_Lozenge                                       0x25CA
#define U_WhiteCircle                                   0x25CB
#define U_DottedCircle                                  0x25CC
#define U_CircleWithVerticalFill                        0x25CD
#define U_Bullseye                                      0x25CE
#define U_BlackCircle                                   0x25CF
#define U_CircleWithLeftHalfBlack                       0x25D0
#define U_CircleWithRightHalfBlack                      0x25D1
#define U_CircleWithLowerHalfBlack                      0x25D2
#define U_CircleWithUpperHalfBlack                      0x25D3
#define U_CircleWithUpperRightQuadrantBlack             0x25D4
#define U_CircleWithAllButUpperLeftQuadrantBlack        0x25D5
#define U_LeftHalfBlackCircle                           0x25D6
#define U_RightHalfBlackCircle                          0x25D7
#define U_InverseBullet                                 0x25D8
#define U_InverseWhiteCircle                            0x25D9
#define U_UpperHalfInverseWhiteCircle                   0x25DA
#define U_LowerHalfInverseWhiteCircle                   0x25DB
#define U_UpperLeftQuadrantCircularArc                  0x25DC
#define U_UpperRightQuadrantCircularArc                 0x25DD
#define U_LowerRightQuadrantCircularArc                 0x25DE
#define U_LowerLeftQuadrantCircularArc                  0x25DF
#define U_UpperHalfCircle                               0x25E0
#define U_LowerHalfCircle                               0x25E1  
#define U_BlackLowerRightTriangle                       0x25E2
#define U_BlackLowerLeftTriangle                        0x25E3
#define U_BlackUpperLeftTriangle                        0x25E4
#define U_BlackUpperRightTriangle                       0x25E5
#define U_WhiteBullet                                   0x25E6
#define U_SquareWithLeftHalfBlack                       0x25E7
#define U_SquareWithRightHalfBlack                      0x25E8
#define U_SquareWithUpperLeftDiagonalHalfBlack          0x25E9
#define U_SquareWithLowerRightDiagonalHalfBlack         0x25EA
#define U_WhiteSquareWithVerticalBisectingLine          0x25EB
#define U_WhiteUpPointingTriangleWithDot                0x25EC
#define U_UpPointingTriangleWithLeftHalfBlack           0x25ED
#define U_UpPointingTriangleWithRightHalfBlack          0x25EE
#define U_LargeCircle                                   0x25EF
#define U_WhiteSquareWithUpperLeftQuadrant              0x25F0
#define U_WhiteSquareWithLowerLeftQuadrant              0x25F1
#define U_WhiteSquareWithLowerRightQuadrant             0x25F2
#define U_WhiteSquareWithUpperRightQuadrant             0x25F3
#define U_WhiteCircleWithUpperLeftQuadrant              0x25F4
#define U_WhiteCircleWithLowerLeftQuadrant              0x25F5
#define U_WhiteCircleWithLowerRightQuadrant             0x25F6
#define U_WhiteCircleWithUpperRightQuadrant             0x25F7
#define U_UpperLeftTriangle                             0x25F8
#define U_UpperRightTriangle                            0x25F9
#define U_LowerLeftTriangle                             0x25FA
#define U_WhiteMediumSquare                             0x25FB
#define U_BlackMediumSquare                             0x25FC
#define U_WhiteMediumSmallSquare                        0x25FD
#define U_BlackMediumSmallSquare                        0x25FE
#define U_LowerRightTriangle                            0x25FF


   /* ------ 2600-26FF: Miscellaneous Symbols ------ */

   /*        Weather and astrological symbols: */
#define U_BlackSunWithRays                              0x2600
#define U_Cloud                                         0x2601
#define U_Umbrella                                      0x2602
#define U_Snowman                                       0x2603
#define U_Comet                                         0x2604
#define U_BlackStar                                     0x2605
#define U_WhiteStar                                     0x2606
#define U_Lightning                                     0x2607
#define U_Thunderstorm                                  0x2608
#define U_Sun                                           0x2609
#define U_AscendingNode                                 0x260A
#define U_DescendingNode                                0x260B
#define U_Conjunction                                   0x260C
#define U_Opposition                                    0x260D

   /*        Miscellaneous symbols: */
#define U_BlackTelephone                                0x260E
#define U_WhiteTelephone                                0x260F
#define U_BallotBox                                     0x2610
#define U_BallotBoxWithCheck                            0x2611
#define U_BallotBoxWithX                                0x2612
#define U_Saltire                                       0x2613
/* #define U_2614                                       0xFFFF      */
/* #define U_2615                                       0xFFFF      */

   /*        Japanese chess symbols: */
#define U_WhiteShogiPiece                               0x2616
#define U_BlackShogiPiece                               0x2617

   /*         Miscellaneous symbol: */
/* #define U_2618                                       0xFFFF      */
#define U_ReversedRotatedFloralHeartBullet              0x2619

   /*         Pointing hand symbols: */
#define U_BlackLeftPointingHand                         0x261A
#define U_BlackRightPointingHand                        0x261B
#define U_WhiteLeftPointingIndex                        0x261C
#define U_WhiteUpPointingIndex                          0x261D
#define U_WhiteRightPointingIndex                       0x261E
#define U_WhiteDownPointingIndex                        0x261F

   /*         Warning signs: */
#define U_SkullAndCrossbones                            0x2620
#define U_CautionSign                                   0x2621
#define U_RadioactiveSign                               0x2622
#define U_BiohazardSign                                 0x2623

   /*         Medical and healing symbols: */
#define U_Cadeceus                                      0x2624
#define U_Ankh                                          0x2625

   /*         Religious and political symbols: */
#define U_OrthodoxCross                                 0x2626
#define U_ChiRho                                        0x2627
#define U_CrossOfLorraine                               0x2628
#define U_CrossOfJerusalem                              0x2629
#define U_StarAndCrescent                               0x262A
#define U_FarsiSymbol                                   0x262B
#define U_AdiShakti                                     0x262C
#define U_HammerAndSickle                               0x262D
#define U_PeaceSymbol                                   0x262E
#define U_YinYang                                       0x262F

   /*         Yijing trigram symbols: */
#define U_TrigramForHeaven                              0x2630
#define U_TrigramForLake                                0x2631
#define U_TrigramForFire                                0x2632
#define U_TrigramForThunder                             0x2633
#define U_TrigramForWind                                0x2634
#define U_TrigramForWater                               0x2635
#define U_TrigramForMountain                            0x2636
#define U_TrigramForEarth                               0x2637

   /*         Miscellaneous symbols: */
#define U_WheelOfDharma                                 0x2638
#define U_WhiteFrowningFace                             0x2639
#define U_WhiteSmilingFace                              0x263A
#define U_BlackSmilingFace                              0x263B
#define U_WhiteSunWithRays                              0x263C

   /*         Astrological symbols: */
#define U_FirstQuarterMoon                              0x263D
#define U_LastQuarterMoon                               0x263E
#define U_Mercury                                       0x263F
#define U_FemaleSign                                    0x2640
#define U_Earth                                         0x2641
#define U_MaleSign                                      0x2642
#define U_Jupiter                                       0x2643
#define U_Saturn                                        0x2644
#define U_Uranus                                        0x2645
#define U_Neptune                                       0x2646
#define U_Pluto                                         0x2647

   /*         Zodiacal symbols: */
#define U_Aries                                         0x2648
#define U_Taurus                                        0x2649
#define U_Gemini                                        0x264A
#define U_Cancer                                        0x264B
#define U_Leo                                           0x264C
#define U_Virgo                                         0x264D
#define U_Libra                                         0x264E
#define U_Scorpius                                      0x264F
#define U_Sagittarius                                   0x2650
#define U_Capricorn                                     0x2651
#define U_Aquarius                                      0x2652
#define U_Pisces                                        0x2653

   /*         Chess symbols: */
#define U_WhiteChessKing                                0x2654
#define U_WhiteChessQueen                               0x2655
#define U_WhiteChessRook                                0x2656
#define U_WhiteChessBishop                              0x2657
#define U_WhiteChessKnight                              0x2658
#define U_WhiteChessPawn                                0x2659
#define U_BlackChessKing                                0x265A
#define U_BlackChessQueen                               0x265B
#define U_BlackChessRook                                0x265C
#define U_BlackChessBishop                              0x265D
#define U_BlackChessKnight                              0x265E
#define U_BlackChessPawn                                0x265F

   /*         Playing card symbols: */
#define U_BlackSpadeSuit                                0x2660
#define U_WhiteHeartSuit                                0x2661
#define U_WhiteDiamondSuit                              0x2662
#define U_BlackClubSuit                                 0x2663
#define U_WhiteSpadSuit                                 0x2664
#define U_BlackHeartSuit                                0x2665
#define U_BlackDiamondSuit                              0x2666
#define U_WhiteClubSuit                                 0x2667

   /*         Miscellaneous symbol: */
#define U_HotSprings                                    0x2668

   /*         Musical symbols: */
#define U_QuarterNote                                   0x2669
#define U_EighthNote                                    0x266A
#define U_BeamedEighthNote                              0x266B
#define U_BeamedSixteenthNote                           0x266C
#define U_MusicFlatSign                                 0x266D
#define U_MusicNaturalSign                              0x266E
#define U_MusicSharpSign                                0x266F

   /*         Syriac cross symbols: */
#define U_WestSyriacCross                               0x2670
#define U_EastSyriacCross                               0x2671

   /*         Recycling symbols: */
#define U_UniversalRecyclingSymbol                      0x2672
#define U_RecyclingSymbolForType1Plastics               0x2673
#define U_RecyclingSymbolForType2Plastics               0x2674
#define U_RecyclingSymbolForType3Plastics               0x2675
#define U_RecyclingSymbolForType4Plastics               0x2676
#define U_RecyclingSymbolForType5Plastics               0x2677
#define U_RecyclingSymbolForType6Plastics               0x2678
#define U_RecyclingSymbolForType7Plastics               0x2679
#define U_RecyclingSymbolForGenericMaterials            0x267A
#define U_BlackUniversalRecyclingSymbol                 0x267B
#define U_RecycledPaperSymbol                           0x267C
#define U_ParticallyRecycledPaperSymbol                 0x267D
/* #define U_267E                                       0xFFFF      */
/* #define U_267F                                       0xFFFF      */

   /*         Dice: */
#define U_DieFace1                                      0x2680
#define U_DieFace2                                      0x2681
#define U_DieFace3                                      0x2682
#define U_DieFace4                                      0x2683
#define U_DieFace5                                      0x2684
#define U_DieFace6                                      0x2685

   /*         Go markers: */
#define U_WhiteCircleWithDotRight                       0x2686
#define U_WhiteCircleWithTwoDots                        0x2687
#define U_BlackCircleWithWhiteDotRright                 0x2688
#define U_BlackCircleWithTwoWhiteDots                   0x2689


   /* ------ 2700-27BF: Dingbats ------ */
   /* ------ 27C0-27EF: Miscellaneous Mathematical Symbols-A ------ */
   /* ------ 27F0-27FF: Supplemental Arrows-A ------ */
   /* ------ 2800-28FF: Braille Patterns ------ */
   /* ------ 2900-297F: Supplemental Arrows-B ------ */
   /* ------ 2980-29FF: Miscellaneous Mathematical Symbols-B ------ */


   
   /* ------ 2A00-2AFF: Supplemental Mathematical Operators ------ */
   /* ------ 2E80-2EFF: CJK Radicals Supplement ------ */
   /* ------ 2F00-2FDF: Kangxi Radicals ------ */
   /* ------ 2FF0-2FFF: Ideographic Description Characters ------ */
   /* ------ 3000-303F: CJK Symbols and Punctuation ------ */
   /* ------ 3040-309F: Hiragana ------ */
   /* ------ 30A0-30FF: Katakana ------ */
   /* ------ 3100-312F: Bopomofo ------ */
   /* ------ 3130-318F: Hangul Compatibility Jamo ------ */
   /* ------ 3190-319F: Kanbun ------ */
   /* ------ 31A0-31BF: Bopomofo Extended ------ */
   /* ------ 3200-32FF: Enclosed CJK Letters and Months ------ */
   /* ------ 3300-33FF: CJK Compatibility ------ */
   /* ------ 3400-4DBF: CJK Unified Ideographs Extension A ------ */
   /* ------ 4E00-9FAF: CJK Unified Ideographs ------ */
   /* ------ A000-A48F: Yi Syllables ------ */
   /* ------ A490-A4CF: Yi Radicals ------ */
   /* ------ AC00-D7AF: Hangul Syllables ------ */
   /* ------ D800-DBFF: High Surrogate Area ------ */
   /* ------ DC00-DFFF: Low Surrogate Area ------ */

   /* ------ E000-F8FF: Private Use Area ------ */

#define U_cz_LeftDoubleQuotationMark                    0xE000  /* cz `` */
#define U_cz_RightDoubleQuotationMark                   0xE001  /* cz '' */
#define U_cz_DoubleLow9QuotationMark                    0xE002  /* cz ,, */

#define U_Apple_AppleLogo                               0xF8FF  /* (c) Apple Inc. */


   /* ------ F900-FAFF: CJK Compatibility Ideographs ------ */

   /* ------ FB00-FB4F: Alphabetic Presentation Forms ------ */
   
#define U_LatinSmallLigatureFF                          0xFB00
#define U_LatinSmallLigatureFI                          0xFB01
#define U_LatinSmallLigatureFL                          0xFB02
   /* ... */                                         /* 0xFB03 .. */


   /* ------ FB50-FDFF: Arabic Presentation Forms-A ------ */
   /* ------ FE00-FE0F: Variation Selectors ------ */
   /* ------ FE20-FE2F: Combining Half Marks ------ */
   /* ------ FE30-FE4F: CJK Compatibility Forms ------ */
   /* ------ FE50-FE6F: Small Form Variants ------ */
   /* ------ FE70-FEFF: Arabic Presentation Forms-B ------ */
   /* ------ FF00-FFEF: Halfwidth and Fullwidth Forms ------ */
   /* ------ FFF0-FFFF: Specials ------ */

#define U_InterlinearAnnotationAnchor                   0xFFF9
#define U_InterlinearAnnotationSeparator                0xFFFA
#define U_InterlinearAnnotationTerminator               0xFFFB
#define U_ObjectReplacementCharacter                    0xFFFC
#define U_ReplacementCharacter                          0xFFFD

   /* the following two are no characters at all!!! */
#define U_FFFE                                          0xFFFE
#define U_FFFF                                          0xFFFF
#define U_NIL                                           0xFFFF


/* !!!!! WARNING !!!!! */
/* ------------------- */
/* As soon as Unicode constants > 0xFFFF are defined, */
/* the relevant tables must no longer use _UWORD, */
/* but have to switch to _ULONG. */


   /* ====== More Unicode character groups defined in general ====== */
   /*       (set defines where you need them)                        */

   /* ------ 10300-1032F: Old Italic ------ */
   /* ------ 10330-1034F: Gothic ------ */
   /* ------ 10400-1044F: Deseret ------ */
   /* ------ 1D000-1D0FF: Byzantine Musical Symbols ------ */
   /* ------ 1D100-1D1FF: Musical Symbols ------ */
   /* ------ 1D400-1D7FF: Mathematical Alphanumeric Symbols ------ */
   /* ------ 20000-2A6DF: CJK Unified Ideographs Extension B ------ */
   /* ------ 2F800-2FA1F: CJK Compatibility Ideographs Supplement ------ */
   /* ------ E0000-E007F: Tags ------ */
   /* ------ F0000-FFFFD: Supplementary Private Use Area-A ------ */
   /* ------ 100000-10FFFD: Supplementary Private Use Area-B ------ */

#endif /* __UNICODE_H__ */
