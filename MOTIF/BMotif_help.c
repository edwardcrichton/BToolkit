/* Copyright (c) 1985-2012, B-Core (UK) Ltd
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following
conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in
   the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT 
NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#include "BMotif_defs.h"

MenuItem Help_BMethod_menu [] = {
  { "BMethod", "",
   ( XtPointer ) "BMethod", ( MenuItem * ) NULL },
  { "Abstract Machine Notation", "",
   ( XtPointer ) "AMNotation", ( MenuItem * ) NULL },
  { "Set Theory Notation", "",
   ( XtPointer ) "MathsNotation", ( MenuItem * ) NULL },
  { "Constructing Specifications", "",
   ( XtPointer ) "Structuring", ( MenuItem * ) NULL },
  { "ASCII Representation", "",
   ( XtPointer ) "ASCIISymbols", ( MenuItem * ) NULL },
  ( XtPointer ) NULL,
};

MenuItem Help_BToolkit_menu [] = {
  { "Getting Started", "",
   ( XtPointer ) "GettingStarted", ( MenuItem * ) NULL },
  { "BToolkit", "",
   ( XtPointer ) "BToolkit", ( MenuItem * ) NULL },
  { "Environment Variables", "",
   ( XtPointer ) "BEnvironment", ( MenuItem * ) NULL },
  { "Bplatform", "",
   ( XtPointer ) "BPlatform", ( MenuItem * ) NULL },
  { "Installation", "",
   ( XtPointer ) "Installation", ( MenuItem * ) NULL },
  { "System Library", "",
   ( XtPointer ) "SystemLibrary", ( MenuItem * ) NULL },
  ( XtPointer ) NULL,
};

MenuItem Help_TopBar_menu [] = {
  { "Set Tool Attributes", "Options",
   ( XtPointer ) "Options", ( MenuItem * ) NULL },
  { "Edit Templates", "Palette",
   ( XtPointer ) "Palette", ( MenuItem * ) NULL },
  ( XtPointer ) NULL,
};

MenuItem Help_ToolBar_menu [] = {
  { "Commit Edits", "Commit",
   ( XtPointer ) "Commit", ( MenuItem * ) NULL },
  { "New Constructs", "Introduce",
   ( XtPointer ) "Introduce", ( MenuItem * ) NULL },
  { "Remake Development", "Remake",
   ( XtPointer ) "Remake", ( MenuItem * ) NULL },
  { "Overview Developments", "Overview",
   ( XtPointer ) "Overview", ( MenuItem * ) NULL },
  { "Hypertext Browse Developments", "Hypertext",
   ( XtPointer ) "Hypertext", ( MenuItem * ) NULL },
  { "Close Edit Windows", "Close",
   ( XtPointer ) "Close", ( MenuItem * ) NULL },
  ( XtPointer ) NULL,
};

MenuItem Help_Utilities_menu [] = {
  { "Find Identifier", "",
   ( XtPointer ) "Find", ( MenuItem * ) NULL },
  { "Rename Construct", "",
   ( XtPointer ) "Rename", ( MenuItem * ) NULL },
  { "Remove Constructs", "",
   ( XtPointer ) "Remove", ( MenuItem * ) NULL },
  { "Reset Constructs", "",
   ( XtPointer ) "Reset", ( MenuItem * ) NULL },
  { "Save Development", "",
   ( XtPointer ) "SaveDevelopment", ( MenuItem * ) NULL },
  { "Create SLIB Construct", "",
   ( XtPointer ) "CreateSLIB", ( MenuItem * ) NULL },
  ( XtPointer ) NULL,
};

MenuItem Help_General_menu [] = {
  { "Commit Edits", "cmt",
   ( XtPointer ) "CommitEdits", ( MenuItem * ) NULL },
  { "Editing", "opn, quit",
   ( XtPointer ) "Editor", ( MenuItem * ) NULL },
  { "Mini Remake", "",
   ( XtPointer ) "MiniRemake", ( MenuItem * ) NULL },
  { "Unlock Development", "BUnlock",
   ( XtPointer ) "BUnlock", ( MenuItem * ) NULL },
  { "Display B Processes", "BProcessInfo",
   ( XtPointer ) "BProcessInfo", ( MenuItem * ) NULL },
  { "BToolkit Licence Manager", "BToolkitd",
   ( XtPointer ) "BToolkitd", ( MenuItem * ) NULL },
  ( XtPointer ) NULL,
};

MenuItem Help_Main_menu [] = {
  { "Analyse Constructs", "anl",
   ( XtPointer ) "Analyser", ( MenuItem * ) NULL },
  { "ProofObligations", "pog",
   ( XtPointer ) "POGenerator", ( MenuItem * ) NULL },
  { "Animation", "anm",
   ( XtPointer ) "Animator", ( MenuItem * ) NULL },
  { "Status", "sts",
   ( XtPointer ) "Status", ( MenuItem * ) NULL },
  { "Reset Construct", "rst",
   ( XtPointer ) "ResetConstruct", ( MenuItem * ) NULL },
  ( XtPointer ) NULL,
};

MenuItem Help_Provers_menu [] = {
  { "Automatic Proofs", "apr, pmd",
   ( XtPointer ) "AutoProver", ( MenuItem * ) NULL },
  { "Interactive Proofs", "ipr, pmd",
   ( XtPointer ) "InterProver", ( MenuItem * ) NULL },
  { "Remove proofs", "rsl",
   ( XtPointer ) "RemoveLevel", ( MenuItem * ) NULL },
  { "Print Proofs", "ppf",
   ( XtPointer ) "ProofPrinter", ( MenuItem * ) NULL },
  { "Show Unproved POs", "sup",
   ( XtPointer ) "ShowUnproved", ( MenuItem * ) NULL },
  ( XtPointer ) NULL,
};

MenuItem Help_Generators_menu [] = {
  { "Data Bases", "gbm, gbo",
   ( XtPointer ) "BaseGen", ( MenuItem * ) NULL },
  { "Enumerated sets", "enum",
   ( XtPointer ) "Enumerator", ( MenuItem * ) NULL },
  { "Interactive Interfaces", "itf",
   ( XtPointer ) "Interface", ( MenuItem * ) NULL },
  ( XtPointer ) NULL,
};

MenuItem Help_Translator_menu [] = {
  { "Translate to Code", "trl",
   ( XtPointer ) "Translator", ( MenuItem * ) NULL },
  { "Link Code", "lnk",
   ( XtPointer ) "Linker", ( MenuItem * ) NULL },
  { "Execute Programs", "run",
   ( XtPointer ) "Run", ( MenuItem * ) NULL },
  ( XtPointer ) NULL,
};

MenuItem Help_Documents_menu [] = {
  { "Mark Up Documents", "dmu",
   ( XtPointer ) "DocumentMarkUp", ( MenuItem * ) NULL },
  { "Document Structure", "",
   ( XtPointer ) "Documents", ( MenuItem * ) NULL },
  { "Show Documents", "shw",
   ( XtPointer ) "Show", ( MenuItem * ) NULL },
  { "Print Documents", "prt",
   ( XtPointer ) "Print", ( MenuItem * ) NULL },
  ( XtPointer ) NULL,
};


MenuItem Help_menus [] = {
  { "Contents", "", ( XtPointer ) "Contents", ( MenuItem * ) NULL },
  { "BMethod", "", ( XtPointer ) NULL, Help_BMethod_menu },
  { "BToolkit", "", ( XtPointer ) NULL, Help_BToolkit_menu },
  { "TopBar", "", ( XtPointer ) NULL, Help_TopBar_menu },
  { "ToolBar", "", ( XtPointer ) NULL, Help_ToolBar_menu },
  { "Utilities", "", ( XtPointer ) NULL, Help_Utilities_menu },
  { "General", "", ( XtPointer ) NULL, Help_General_menu },
  { "Main", "", ( XtPointer ) NULL, Help_Main_menu },
  { "Provers", "", ( XtPointer ) NULL, Help_Provers_menu },
  { "Generators", "", ( XtPointer ) NULL, Help_Generators_menu },
  { "Translator", "", ( XtPointer ) NULL, Help_Translator_menu },
  { "Documents", "", ( XtPointer ) NULL, Help_Documents_menu },
  { "Index", "", ( XtPointer ) "Index", ( MenuItem * ) NULL },
  ( XtPointer ) NULL,
};



#define Palette_menu_tot 20

char *Palette_menu [] = {
  "Machines.pal",  "Machines",
  "OpsMch.pal",  "Machine Ops",
  "Refinements.pal",  "Refinements",
  "OpsRef.pal",  "Refinement Ops",
  "Implementations.pal",  "Implementations",
  "OpsImp.pal",  "Implementation Ops",
  "Bases.pal",  "Bases",
  "Documents.pal",  "Documents",
  "Enumerations.pal",  "Enumerations",
  "Interfaces.pal",  "Interfaces",
};
