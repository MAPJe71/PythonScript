
#include "stdafx.h"
#include "NotepadPlusWrapper.h"
#include "ScintillaWrapper.h"

#include "ProcessExecute.h"

namespace NppPythonScript
{
	void translateProcessStart(const process_start_exception &e)
	{
		PyErr_SetString(PyExc_RuntimeError, e.what());
	}

void export_notepad()
{
	//lint -e1793 While calling �Symbol�: Initializing the implicit object parameter �Type� (a non-const reference) with a non-lvalue
	// The class and enum declarations are used as designed, but they mess up Lint.
	boost::python::register_exception_translator<process_start_exception>(&translateProcessStart);
	boost::python::class_<NotepadPlusWrapper>("Notepad", boost::python::no_init)
		.def("new", &NotepadPlusWrapper::newDocument, "Create a new document")
		.def("new", &NotepadPlusWrapper::newDocumentWithFilename, "Create a new document with the given filename")
		.def("save", &NotepadPlusWrapper::save, "Save the current file")
		.def("saveAs", &NotepadPlusWrapper::saveAs, boost::python::args("filename"), "Save the current file as the specified filename")
		.def("saveAsCopy", &NotepadPlusWrapper::saveAsCopy, boost::python::args("filename"), "Save the current file as the specified filename, but don't change the filename")
		.def("open", &NotepadPlusWrapper::open, boost::python::args("filename"), "Open a new document with the given filename")
		.def("getCurrentView", &NotepadPlusWrapper::getCurrentView, "Get the currently active view (0 or 1)")
		.def("getCurrentLang", &NotepadPlusWrapper::getCurrentLangType, "Get the current language type (returns the LANGTYPE.xxx constants)")
		.def("getFiles", &NotepadPlusWrapper::getFiles, "Gets a list of the open filenames, as a list of tuples (filename, bufferID, index, view)")
		.def("loadSession", &NotepadPlusWrapper::loadSession, boost::python::args("sessionFileName"), "Loads a session from a session file")
		.def("saveSession", &NotepadPlusWrapper::saveSession, boost::python::args("sessionFileName", "listOfFileNames"), "Saves a session file with the list of files (sessionFilename, filesList)")
		.def("getSessionFiles", &NotepadPlusWrapper::getSessionFiles, boost::python::args("sessionFileName"), "Gets a list of files within a session file")
		.def("saveCurrentSession", &NotepadPlusWrapper::saveCurrentSession, boost::python::args("sessionFileName"), "Save the current session (filename)")
		.def("createScintilla", &NotepadPlusWrapper::createScintilla, "Create a new Scintilla handle. Returns an Editor object")
		.def("destroyScintilla", &NotepadPlusWrapper::destroyScintilla, boost::python::args("editor"), "Destroy a Scintilla handle created with createScintilla.")
		.def("getCurrentDocIndex", &NotepadPlusWrapper::getCurrentDocIndex, boost::python::args("view"), "Gets the current active index for the given view (0 or 1)")
		.def("setStatusBar", &NotepadPlusWrapper::setStatusBar, boost::python::args("section", "text"), "Sets the status bar text. Call with the STATUSBARSECTION, and the string to show")
		.def("getPluginMenuHandle", &NotepadPlusWrapper::getPluginMenuHandle, "Gets the handle for the Plugins menu.")
		.def("activateIndex", &NotepadPlusWrapper::activateIndex, boost::python::args("view", "index"), "Activates the document with the given view and index (view, index)")
		.def("reloadFile", &NotepadPlusWrapper::reloadFile, boost::python::args("filename", "alertUser"), "Reloads a filename.")
		.def("saveAllFiles", &NotepadPlusWrapper::saveAllFiles, "Saves all currently unsaved files")
		.def("getPluginConfigDir", &NotepadPlusWrapper::getPluginConfigDir, "Gets the plugin config directory")
		.def("menuCommand", &NotepadPlusWrapper::menuCommand, boost::python::args("commandID"), "Runs a Notepad++ menu command - just pass the commandID (from the nativeLang file, or a MENUCOMMAND constant)")
		.def("getVersion", &NotepadPlusWrapper::getVersion, "Gets the Notepad++ version as a tuple - e.g. 5.6.8 becomes (5,6,8)")
		.def("hideTabBar", &NotepadPlusWrapper::hideTabBar, "Hides the Tab bar")
		.def("showTabBar", &NotepadPlusWrapper::showTabBar, "Shows the Tab bar")
		.def("getCurrentBufferID", &NotepadPlusWrapper::getCurrentBufferID, "Gets the bufferID of the currently active buffer")
		.def("reloadBuffer", &NotepadPlusWrapper::reloadBuffer, "Reloads a buffer - just pass the buffer ID")
		.def("getLangType", &NotepadPlusWrapper::getLangType, "Gets the language type of the current buffer. Pass a buffer ID to get the type of the specified buffer.")
		.def("getLangType", &NotepadPlusWrapper::getBufferLangType, "Gets the language type of the current buffer. Pass a buffer ID to get the type of the specified buffer.")
		.def("setLangType", &NotepadPlusWrapper::setCurrentLangType, boost::python::args("langType"), "Set the current language type (use LANGTYPE.xxx constants)")
		.def("setLangType", &NotepadPlusWrapper::setBufferLangType, boost::python::args("langType", "bufferID"), "Sets the language type of the current buffer. Pass a buffer ID as the second parameter to set the language for a specific buffer.")
		.def("getEncoding", &NotepadPlusWrapper::getEncoding, "Gets the encoding of the current buffer.  Pass a buffer ID to get the encoding of a specific buffer.")
		.def("getEncoding", &NotepadPlusWrapper::getBufferEncoding, "Gets the encoding of the current buffer.  Pass a buffer ID to get the encoding of a specific buffer.")
		.def("setEncoding", &NotepadPlusWrapper::setEncoding, boost::python::args("encoding"), "Sets the encoding of the current buffer.  Use the BUFFERENCODING constants")
		.def("setEncoding", &NotepadPlusWrapper::setBufferEncoding, boost::python::args("encoding", "bufferID"), "Sets the encoding of the given bufferID.  Use the BUFFERENCODING constants to specify the encoding")		
		.def("getFormatType", &NotepadPlusWrapper::getFormatType, "Gets the format type (i.e. Windows, Unix or Mac) of the current buffer.  Pass a buffer ID to get the format type of a specific buffer.")
		.def("getFormatType", &NotepadPlusWrapper::getBufferFormatType, boost::python::args("bufferID"), "Gets the format type (i.e. Windows, Unix or Mac) of the given bufferID")
		.def("setFormatType", &NotepadPlusWrapper::setFormatType, boost::python::args("formatType"),"Sets the format type (i.e. Windows, Unix or Mac) of the current buffer - use the FORMATTYPE enum.")
		.def("setFormatType", &NotepadPlusWrapper::setBufferFormatType, boost::python::args("formatType", "bufferID"), "Sets the format type (i.e. Windows, Unix or Mac) of the given buffer - use the FORMATTYPE enum.")
		.def("callback", &NotepadPlusWrapper::addCallback, boost::python::args("callable", "listOfNotifications"), "Registers a callback function for a notification. Arguments are (function, [list of NOTIFICATION IDs])")
		.def("activateFile", &NotepadPlusWrapper::activateFileString, boost::python::args("filename"), "Activates the document with the given filename")
		.def("close", &NotepadPlusWrapper::closeDocument, "Closes the currently active document")
		.def("closeAll", &NotepadPlusWrapper::closeAllDocuments, "Closes all open documents")
		.def("closeAllButCurrent", &NotepadPlusWrapper::closeAllButCurrentDocument, "Closes all but the currently active document")
		.def("reloadCurrentDocument", &NotepadPlusWrapper::reloadCurrentDocument, "Reloads the current document")
		.def("getCurrentFilename", &NotepadPlusWrapper::getCurrentFilename, "Gets the filename of the active document")
		.def("getBufferFilename", &NotepadPlusWrapper::getBufferFilename, boost::python::args("bufferID"), "Gets the filename of the given buffer ID")
		.def("activateBufferID", &NotepadPlusWrapper::activateBufferID, boost::python::args("bufferID"), "Activates the given bufferID")
		.def("messageBox", &NotepadPlusWrapper::messageBox, "Displays a message box. messageBox(message[, title[, flags]]).\nFlags can be 0 for a standard 'OK' message box, or a combination of MessageBoxFlags")
		.def("messageBox", &NotepadPlusWrapper::messageBoxNoFlags, "Displays a message box. messageBox(message[, title[, flags]]).\nFlags can be 0 for a standard 'OK' message box, or a combination of MessageBoxFlags")
		.def("messageBox", &NotepadPlusWrapper::messageBoxNoTitle, "Displays a message box. messageBox(message[, title[, flags]]).\nFlags can be 0 for a standard 'OK' message box, or a combination of MessageBoxFlags")
		.def("prompt", &NotepadPlusWrapper::promptDefault, boost::python::args("prompt", "title"), "Prompts the user for some text. enteredText = prompt(prompt, title). Returns None if cancelled")
		.def("prompt", &NotepadPlusWrapper::prompt, boost::python::args("prompt", "title", "defaultText"), "Prompts the user for some text. enteredText = prompt(prompt, title, defaultText). Returns None if cancelled")
		.def("runPluginCommand", &NotepadPlusWrapper::runPluginCommand, boost::python::args("pluginName", "optionName", "refreshMenuItemCache"), "Runs a command from the plugin menu.\nUse to run direct commands from the Plugins menu.\nTo call TextFX or other menu functions, either use notepad.menuCommand() (for Notepad++ menu commands), or notepad.runMenuCommand(menuName, menuOption) for TextFX or non built-in menus.")
		.def("runPluginCommand", &NotepadPlusWrapper::runPluginCommandNoRefresh, boost::python::args("pluginName", "optionName"), "Runs a command from the plugin menu.\nUse to run direct commands from the Plugins menu.\nTo call TextFX or other menu functions, either use notepad.menuCommand() (for Notepad++ menu commands), or notepad.runMenuCommand(menuName, menuOption) for TextFX or non built-in menus.\nrunPluginCommand(pluginName, menuOptionTitle)")
		.def("runMenuCommand", &NotepadPlusWrapper::runMenuCommand, boost::python::args("menuName", "optionName", "refreshMenuItemCache"), "Runs a command from the menus. For built-in menus use notepad.menuCommand(), for non built-in menus (e.g. TextFX), use notepad.runMenuCommand(menuName, menuOption[, refreshCache]).\n runMenuCommand('TextFX Edit', 'Delete Blank Lines')\n If refreshCache is true, then the menus will be searched again.")
		.def("runMenuCommand", &NotepadPlusWrapper::runMenuCommandNoRefresh, boost::python::args("menuName", "optionName"), "Runs a command from the menus. For built-in menus use notepad.menuCommand(), for non built-in menus (e.g. TextFX), use notepad.runMenuCommand(menuName, menuOption[, refreshCache]).\n runMenuCommand('TextFX Edit', 'Delete Blank Lines')\n If refreshCache is true, then the menus will be searched again.")
		.def("clearCallbacks", &NotepadPlusWrapper::clearAllCallbacks, "Clears all callbacks")
		.def("clearCallbacks", &NotepadPlusWrapper::clearCallbackFunction, boost::python::args("callable"), "Clears all callbacks for the given function")
		.def("clearCallbacks", &NotepadPlusWrapper::clearCallbackEvents, boost::python::args("notificationList"), "Clears all callbacks for the given list of events - list of NOTIFICATION constants")
		.def("clearCallbacks", &NotepadPlusWrapper::clearCallback, boost::python::args("callable", "notificationList"), "Clears the callback for the given callback function for the list of events (NOTIFICATION constants)")
		.def("getNppDir", &NotepadPlusWrapper::getNppDir, "Gets the Notepad++.exe directory")
		.def("getCommandLine", &NotepadPlusWrapper::getCommandLine, "Gets the command line used to start Notepad++")
		.def("allocateSupported", &NotepadPlusWrapper::allocateSupported, "Returns True if the Command ID allocation API is supported in this version of Notepad++")
		.def("allocateCmdID", &NotepadPlusWrapper::allocateCmdID, "allocateCmdID(numberRequested) -> int\nAllocates a Command ID for use in WM_COMMAND. Mainly used internally by plugins.")
		.def("allocateMarker", &NotepadPlusWrapper::allocateMarker, "allocateMarker(numberRequested) -> int\nAllocates a marker number for Scintilla. Use this to stop marker number collisions with other plugins / scripts.")
		.def("getPluginVersion", &NotepadPlusWrapper::getPluginVersion, "getPluginVersion() -> str\nGets the version number of the PythonScript plugin, in the format '0.9.0.1'");



	boost::python::enum_<LangType>("LANGTYPE")
			.value("TXT", L_TXT)
			.value("PHP", L_PHP)
			.value("C", L_C)
			.value("CPP", L_CPP)
			.value("CS", L_CS)
			.value("OBJC", L_OBJC)
			.value("JAVA", L_JAVA)
			.value("RC", L_RC)
			.value("HTML", L_HTML)
			.value("XML", L_XML)
			.value("MAKEFILE", L_MAKEFILE)
			.value("PASCAL", L_PASCAL)
			.value("BATCH", L_BATCH)
			.value("INI", L_INI)
			.value("NFO", L_NFO)
			.value("USER", L_USER)
			.value("ASP", L_ASP)
			.value("SQL", L_SQL)
			.value("VB", L_VB)
			.value("JS", L_JS)
			.value("CSS", L_CSS)
			.value("PERL", L_PERL)
			.value("PYTHON", L_PYTHON)
			.value("LUA", L_LUA)
			.value("TEX", L_TEX)
			.value("FORTRAN", L_FORTRAN)
			.value("BASH", L_BASH)
			.value("FLASH", L_FLASH)
			.value("NSIS", L_NSIS)
			.value("TCL", L_TCL)
			.value("LISP", L_LISP)
			.value("SCHEME", L_SCHEME)
			.value("ASM", L_ASM)
			.value("DIFF", L_DIFF)
			.value("PROPS", L_PROPS)
			.value("PS", L_PS)
			.value("RUBY", L_RUBY)
			.value("SMALLTALK", L_SMALLTALK)
			.value("VHDL", L_VHDL)
			.value("KIX", L_KIX)
			.value("AU3", L_AU3)
			.value("CAML", L_CAML)
			.value("ADA", L_ADA)
			.value("VERILOG", L_VERILOG)
			.value("MATLAB", L_MATLAB)
			.value("HASKELL", L_HASKELL)
			.value("INNO", L_INNO)
			.value("SEARCHRESULT", L_SEARCHRESULT)
			.value("CMAKE", L_CMAKE)
			.value("YAML", L_YAML);

	boost::python::enum_<FormatType>("FORMATTYPE")
		.value("WIN", WIN_FORMAT)
		.value("MAC", MAC_FORMAT)
		.value("UNIX", UNIX_FORMAT);

	boost::python::enum_<BufferEncoding>("BUFFERENCODING")
		.value("ENC8BIT", uni8Bit)
		.value("UTF8", uniUTF8)
		.value("UCS2BE", uni16BE)
		.value("UCS2LE", uni16LE)
		.value("COOKIE", uniCookie)
		.value("ANSI", uni7Bit)
		.value("UCS2BE_NOBOM", uni16BE_NoBOM)
		.value("UCS2LE_NOBOM", uni16LE_NoBOM);
	
	boost::python::enum_<StatusBarSection>("STATUSBARSECTION")
		.value("DOCTYPE", STATUSBARSECTION_DOCTYPE)
		.value("DOCSIZE", STATUSBARSECTION_DOCSIZE)
		.value("CURPOS", STATUSBARSECTION_CURPOS)
		.value("EOFFORMAT", STATUSBARSECTION_EOFFORMAT)
		.value("UNICODETYPE", STATUSBARSECTION_UNICODETYPE)
		.value("TYPINGMODE", STATUSBARSECTION_TYPINGMODE);

	boost::python::enum_<Notification>("NOTIFICATION")
		.value("READY", NPPNOTIF_READY)
		.value("TBMODIFICATION", NPPNOTIF_TBMODIFICATION)
		.value("FILEBEFORECLOSE", NPPNOTIF_FILEBEFORECLOSE)
		.value("FILEOPENED", NPPNOTIF_FILEOPENED)
		.value("FILECLOSED", NPPNOTIF_FILECLOSED)
		.value("FILEBEFOREOPEN", NPPNOTIF_FILEBEFOREOPEN)
		.value("FILEBEFORESAVE", NPPNOTIF_FILEBEFORESAVE)
		.value("FILESAVED", NPPNOTIF_FILESAVED)
		.value("SHUTDOWN", NPPNOTIF_SHUTDOWN)
		.value("BUFFERACTIVATED", NPPNOTIF_BUFFERACTIVATED)
		.value("LANGCHANGED", NPPNOTIF_LANGCHANGED)
		.value("WORDSTYLESUPDATED", NPPNOTIF_WORDSTYLESUPDATED)
		.value("SHORTCUTREMAPPED", NPPNOTIF_SHORTCUTREMAPPED)
		.value("FILEBEFORELOAD", NPPNOTIF_FILEBEFORELOAD)
		.value("FILELOADFAILED", NPPNOTIF_FILELOADFAILED)
		.value("READONLYCHANGED", NPPNOTIF_READONLYCHANGED);

	boost::python::enum_<MessageBoxFlags>("MESSAGEBOXFLAGS")
		.value("OK", NPPMB_OK)
		.value("OKCANCEL", NPPMB_OKCANCEL)
		.value("ABORTRETRYIGNORE", NPPMB_ABORTRETRYIGNORE)
		.value("YESNOCANCEL", NPPMB_YESNOCANCEL)
		.value("YESNO", NPPMB_YESNO)
		.value("RETRYCANCEL", NPPMB_RETRYCANCEL)
		.value("CANCELTRYCONTINUE", NPPMB_CANCELTRYCONTINUE)
		.value("ICONHAND", NPPMB_ICONHAND)
		.value("ICONQUESTION", NPPMB_ICONQUESTION)
		.value("ICONEXCLAMATION", NPPMB_ICONEXCLAMATION)
		.value("ICONASTERISK", NPPMB_ICONASTERISK)
		.value("ICONWARNING", NPPMB_ICONWARNING)
		.value("ICONERROR", NPPMB_ICONERROR)
		.value("ICONINFORMATION", NPPMB_ICONINFORMATION)
		.value("ICONSTOP", NPPMB_ICONSTOP)
		.value("DEFBUTTON1", NPPMB_DEFBUTTON1)
		.value("DEFBUTTON2", NPPMB_DEFBUTTON2)
		.value("DEFBUTTON3", NPPMB_DEFBUTTON3)
		.value("DEFBUTTON4", NPPMB_DEFBUTTON4)
		.value("RESULTCONTINUE", NPPMB_RESULTCONTINUE)
		.value("RESULTABORT", NPPMB_RESULTABORT)
		.value("RESULTCANCEL", NPPMB_RESULTCANCEL)
		.value("RESULTIGNORE", NPPMB_RESULTIGNORE)
		.value("RESULTNO", NPPMB_RESULTNO)
		.value("RESULTOK", NPPMB_RESULTOK)
		.value("RESULTRETRY", NPPMB_RESULTRETRY)
		.value("RESULTTRYAGAIN", NPPMB_RESULTTRYAGAIN)
		.value("RESULTYES", NPPMB_RESULTYES);


	boost::python::enum_<MenuCommands>("MENUCOMMAND")
		.value("FILE_NEW", NPPIDM_FILE_NEW)
		.value("FILE_OPEN", NPPIDM_FILE_OPEN)
		.value("FILE_CLOSE", NPPIDM_FILE_CLOSE)
		.value("FILE_CLOSEALL", NPPIDM_FILE_CLOSEALL)
		.value("FILE_CLOSEALL_BUT_CURRENT", NPPIDM_FILE_CLOSEALL_BUT_CURRENT)
		.value("FILE_SAVE", NPPIDM_FILE_SAVE)
		.value("FILE_SAVEALL", NPPIDM_FILE_SAVEALL)
		.value("FILE_SAVEAS", NPPIDM_FILE_SAVEAS)
		.value("FILE_PRINT", NPPIDM_FILE_PRINT)
		.value("FILE_PRINTNOW", NPPIDM_FILE_PRINTNOW)
		.value("FILE_EXIT", NPPIDM_FILE_EXIT)
		.value("FILE_LOADSESSION", NPPIDM_FILE_LOADSESSION)
		.value("FILE_SAVESESSION", NPPIDM_FILE_SAVESESSION)
		.value("FILE_RELOAD", NPPIDM_FILE_RELOAD)
		.value("FILE_SAVECOPYAS", NPPIDM_FILE_SAVECOPYAS)
		.value("FILE_DELETE", NPPIDM_FILE_DELETE)
		.value("FILE_RENAME", NPPIDM_FILE_RENAME)
		.value("EDIT_CUT", NPPIDM_EDIT_CUT)
		.value("EDIT_COPY", NPPIDM_EDIT_COPY)
		.value("EDIT_UNDO", NPPIDM_EDIT_UNDO)
		.value("EDIT_REDO", NPPIDM_EDIT_REDO)
		.value("EDIT_PASTE", NPPIDM_EDIT_PASTE)
		.value("EDIT_DELETE", NPPIDM_EDIT_DELETE)
		.value("EDIT_SELECTALL", NPPIDM_EDIT_SELECTALL)
		.value("EDIT_INS_TAB", NPPIDM_EDIT_INS_TAB)
		.value("EDIT_RMV_TAB", NPPIDM_EDIT_RMV_TAB)
		.value("EDIT_DUP_LINE", NPPIDM_EDIT_DUP_LINE)
		.value("EDIT_TRANSPOSE_LINE", NPPIDM_EDIT_TRANSPOSE_LINE)
		.value("EDIT_SPLIT_LINES", NPPIDM_EDIT_SPLIT_LINES)
		.value("EDIT_JOIN_LINES", NPPIDM_EDIT_JOIN_LINES)
		.value("EDIT_LINE_UP", NPPIDM_EDIT_LINE_UP)
		.value("EDIT_LINE_DOWN", NPPIDM_EDIT_LINE_DOWN)
		.value("EDIT_UPPERCASE", NPPIDM_EDIT_UPPERCASE)
		.value("EDIT_LOWERCASE", NPPIDM_EDIT_LOWERCASE)
		.value("MACRO_STARTRECORDINGMACRO", NPPIDM_MACRO_STARTRECORDINGMACRO)
		.value("MACRO_STOPRECORDINGMACRO", NPPIDM_MACRO_STOPRECORDINGMACRO)
		.value("MACRO_PLAYBACKRECORDEDMACRO", NPPIDM_MACRO_PLAYBACKRECORDEDMACRO)
		.value("EDIT_BLOCK_COMMENT", NPPIDM_EDIT_BLOCK_COMMENT)
		.value("EDIT_STREAM_COMMENT", NPPIDM_EDIT_STREAM_COMMENT)
		.value("EDIT_TRIMTRAILING", NPPIDM_EDIT_TRIMTRAILING)
		.value("MACRO_SAVECURRENTMACRO", NPPIDM_MACRO_SAVECURRENTMACRO)
		.value("EDIT_RTL", NPPIDM_EDIT_RTL)
		.value("EDIT_LTR", NPPIDM_EDIT_LTR)
		.value("EDIT_SETREADONLY", NPPIDM_EDIT_SETREADONLY)
		.value("EDIT_FULLPATHTOCLIP", NPPIDM_EDIT_FULLPATHTOCLIP)
		.value("EDIT_FILENAMETOCLIP", NPPIDM_EDIT_FILENAMETOCLIP)
		.value("EDIT_CURRENTDIRTOCLIP", NPPIDM_EDIT_CURRENTDIRTOCLIP)
		.value("MACRO_RUNMULTIMACRODLG", NPPIDM_MACRO_RUNMULTIMACRODLG)
		.value("EDIT_CLEARREADONLY", NPPIDM_EDIT_CLEARREADONLY)
		.value("EDIT_COLUMNMODE", NPPIDM_EDIT_COLUMNMODE)
		.value("EDIT_BLOCK_COMMENT_SET", NPPIDM_EDIT_BLOCK_COMMENT_SET)
		.value("EDIT_BLOCK_UNCOMMENT", NPPIDM_EDIT_BLOCK_UNCOMMENT)
		.value("EDIT_AUTOCOMPLETE", NPPIDM_EDIT_AUTOCOMPLETE)
		.value("EDIT_AUTOCOMPLETE_CURRENTFILE", NPPIDM_EDIT_AUTOCOMPLETE_CURRENTFILE)
		.value("EDIT_FUNCCALLTIP", NPPIDM_EDIT_FUNCCALLTIP)
		.value("OPEN_ALL_RECENT_FILE", NPPIDM_OPEN_ALL_RECENT_FILE)
		.value("CLEAN_RECENT_FILE_LIST", NPPIDM_CLEAN_RECENT_FILE_LIST)
		.value("SEARCH_FIND", NPPIDM_SEARCH_FIND)
		.value("SEARCH_FINDNEXT", NPPIDM_SEARCH_FINDNEXT)
		.value("SEARCH_REPLACE", NPPIDM_SEARCH_REPLACE)
		.value("SEARCH_GOTOLINE", NPPIDM_SEARCH_GOTOLINE)
		.value("SEARCH_TOGGLE_BOOKMARK", NPPIDM_SEARCH_TOGGLE_BOOKMARK)
		.value("SEARCH_NEXT_BOOKMARK", NPPIDM_SEARCH_NEXT_BOOKMARK)
		.value("SEARCH_PREV_BOOKMARK", NPPIDM_SEARCH_PREV_BOOKMARK)
		.value("SEARCH_CLEAR_BOOKMARKS", NPPIDM_SEARCH_CLEAR_BOOKMARKS)
		.value("SEARCH_GOTOMATCHINGBRACE", NPPIDM_SEARCH_GOTOMATCHINGBRACE)
		.value("SEARCH_FINDPREV", NPPIDM_SEARCH_FINDPREV)
		.value("SEARCH_FINDINCREMENT", NPPIDM_SEARCH_FINDINCREMENT)
		.value("SEARCH_FINDINFILES", NPPIDM_SEARCH_FINDINFILES)
		.value("SEARCH_VOLATILE_FINDNEXT", NPPIDM_SEARCH_VOLATILE_FINDNEXT)
		.value("SEARCH_VOLATILE_FINDPREV", NPPIDM_SEARCH_VOLATILE_FINDPREV)
		.value("SEARCH_CUTMARKEDLINES", NPPIDM_SEARCH_CUTMARKEDLINES)
		.value("SEARCH_COPYMARKEDLINES", NPPIDM_SEARCH_COPYMARKEDLINES)
		.value("SEARCH_PASTEMARKEDLINES", NPPIDM_SEARCH_PASTEMARKEDLINES)
		.value("SEARCH_DELETEMARKEDLINES", NPPIDM_SEARCH_DELETEMARKEDLINES)
		.value("SEARCH_MARKALLEXT1", NPPIDM_SEARCH_MARKALLEXT1)
		.value("SEARCH_UNMARKALLEXT1", NPPIDM_SEARCH_UNMARKALLEXT1)
		.value("SEARCH_MARKALLEXT2", NPPIDM_SEARCH_MARKALLEXT2)
		.value("SEARCH_UNMARKALLEXT2", NPPIDM_SEARCH_UNMARKALLEXT2)
		.value("SEARCH_MARKALLEXT3", NPPIDM_SEARCH_MARKALLEXT3)
		.value("SEARCH_UNMARKALLEXT3", NPPIDM_SEARCH_UNMARKALLEXT3)
		.value("SEARCH_MARKALLEXT4", NPPIDM_SEARCH_MARKALLEXT4)
		.value("SEARCH_UNMARKALLEXT4", NPPIDM_SEARCH_UNMARKALLEXT4)
		.value("SEARCH_MARKALLEXT5", NPPIDM_SEARCH_MARKALLEXT5)
		.value("SEARCH_UNMARKALLEXT5", NPPIDM_SEARCH_UNMARKALLEXT5)
		.value("SEARCH_CLEARALLMARKS", NPPIDM_SEARCH_CLEARALLMARKS)
		.value("SEARCH_GOPREVMARKER1", NPPIDM_SEARCH_GOPREVMARKER1)
		.value("SEARCH_GOPREVMARKER2", NPPIDM_SEARCH_GOPREVMARKER2)
		.value("SEARCH_GOPREVMARKER3", NPPIDM_SEARCH_GOPREVMARKER3)
		.value("SEARCH_GOPREVMARKER4", NPPIDM_SEARCH_GOPREVMARKER4)
		.value("SEARCH_GOPREVMARKER5", NPPIDM_SEARCH_GOPREVMARKER5)
		.value("SEARCH_GOPREVMARKER_DEF", NPPIDM_SEARCH_GOPREVMARKER_DEF)
		.value("SEARCH_GONEXTMARKER1", NPPIDM_SEARCH_GONEXTMARKER1)
		.value("SEARCH_GONEXTMARKER2", NPPIDM_SEARCH_GONEXTMARKER2)
		.value("SEARCH_GONEXTMARKER3", NPPIDM_SEARCH_GONEXTMARKER3)
		.value("SEARCH_GONEXTMARKER4", NPPIDM_SEARCH_GONEXTMARKER4)
		.value("SEARCH_GONEXTMARKER5", NPPIDM_SEARCH_GONEXTMARKER5)
		.value("SEARCH_GONEXTMARKER_DEF", NPPIDM_SEARCH_GONEXTMARKER_DEF)
		.value("FOCUS_ON_FOUND_RESULTS", NPPIDM_FOCUS_ON_FOUND_RESULTS)
		.value("SEARCH_GOTONEXTFOUND", NPPIDM_SEARCH_GOTONEXTFOUND)
		.value("SEARCH_GOTOPREVFOUND", NPPIDM_SEARCH_GOTOPREVFOUND)
		.value("SEARCH_SETANDFINDNEXT", NPPIDM_SEARCH_SETANDFINDNEXT)
		.value("SEARCH_SETANDFINDPREV", NPPIDM_SEARCH_SETANDFINDPREV)
		.value("VIEW_TOOLBAR_REDUCE", NPPIDM_VIEW_TOOLBAR_REDUCE)
		.value("VIEW_TOOLBAR_ENLARGE", NPPIDM_VIEW_TOOLBAR_ENLARGE)
		.value("VIEW_TOOLBAR_STANDARD", NPPIDM_VIEW_TOOLBAR_STANDARD)
		.value("VIEW_REDUCETABBAR", NPPIDM_VIEW_REDUCETABBAR)
		.value("VIEW_LOCKTABBAR", NPPIDM_VIEW_LOCKTABBAR)
		.value("VIEW_DRAWTABBAR_TOPBAR", NPPIDM_VIEW_DRAWTABBAR_TOPBAR)
		.value("VIEW_DRAWTABBAR_INACIVETAB", NPPIDM_VIEW_DRAWTABBAR_INACIVETAB)
		.value("VIEW_POSTIT", NPPIDM_VIEW_POSTIT)
		.value("VIEW_TOGGLE_FOLDALL", NPPIDM_VIEW_TOGGLE_FOLDALL)
		.value("VIEW_USER_DLG", NPPIDM_VIEW_USER_DLG)
		.value("VIEW_LINENUMBER", NPPIDM_VIEW_LINENUMBER)
		.value("VIEW_SYMBOLMARGIN", NPPIDM_VIEW_SYMBOLMARGIN)
		.value("VIEW_FOLDERMAGIN", NPPIDM_VIEW_FOLDERMAGIN)
		.value("VIEW_FOLDERMAGIN_SIMPLE", NPPIDM_VIEW_FOLDERMAGIN_SIMPLE)
		.value("VIEW_FOLDERMAGIN_ARROW", NPPIDM_VIEW_FOLDERMAGIN_ARROW)
		.value("VIEW_FOLDERMAGIN_CIRCLE", NPPIDM_VIEW_FOLDERMAGIN_CIRCLE)
		.value("VIEW_FOLDERMAGIN_BOX", NPPIDM_VIEW_FOLDERMAGIN_BOX)
		.value("VIEW_ALL_CHARACTERS", NPPIDM_VIEW_ALL_CHARACTERS)
		.value("VIEW_INDENT_GUIDE", NPPIDM_VIEW_INDENT_GUIDE)
		.value("VIEW_CURLINE_HILITING", NPPIDM_VIEW_CURLINE_HILITING)
		.value("VIEW_WRAP", NPPIDM_VIEW_WRAP)
		.value("VIEW_ZOOMIN", NPPIDM_VIEW_ZOOMIN)
		.value("VIEW_ZOOMOUT", NPPIDM_VIEW_ZOOMOUT)
		.value("VIEW_TAB_SPACE", NPPIDM_VIEW_TAB_SPACE)
		.value("VIEW_EOL", NPPIDM_VIEW_EOL)
		.value("VIEW_EDGELINE", NPPIDM_VIEW_EDGELINE)
		.value("VIEW_EDGEBACKGROUND", NPPIDM_VIEW_EDGEBACKGROUND)
		.value("VIEW_TOGGLE_UNFOLDALL", NPPIDM_VIEW_TOGGLE_UNFOLDALL)
		.value("VIEW_FOLD_CURRENT", NPPIDM_VIEW_FOLD_CURRENT)
		.value("VIEW_UNFOLD_CURRENT", NPPIDM_VIEW_UNFOLD_CURRENT)
		.value("VIEW_FULLSCREENTOGGLE", NPPIDM_VIEW_FULLSCREENTOGGLE)
		.value("VIEW_ZOOMRESTORE", NPPIDM_VIEW_ZOOMRESTORE)
		.value("VIEW_ALWAYSONTOP", NPPIDM_VIEW_ALWAYSONTOP)
		.value("VIEW_SYNSCROLLV", NPPIDM_VIEW_SYNSCROLLV)
		.value("VIEW_SYNSCROLLH", NPPIDM_VIEW_SYNSCROLLH)
		.value("VIEW_EDGENONE", NPPIDM_VIEW_EDGENONE)
		.value("VIEW_DRAWTABBAR_CLOSEBOTTUN", NPPIDM_VIEW_DRAWTABBAR_CLOSEBOTTUN)
		.value("VIEW_DRAWTABBAR_DBCLK2CLOSE", NPPIDM_VIEW_DRAWTABBAR_DBCLK2CLOSE)
		.value("VIEW_REFRESHTABAR", NPPIDM_VIEW_REFRESHTABAR)
		.value("VIEW_WRAP_SYMBOL", NPPIDM_VIEW_WRAP_SYMBOL)
		.value("VIEW_HIDELINES", NPPIDM_VIEW_HIDELINES)
		.value("VIEW_DRAWTABBAR_VERTICAL", NPPIDM_VIEW_DRAWTABBAR_VERTICAL)
		.value("VIEW_DRAWTABBAR_MULTILINE", NPPIDM_VIEW_DRAWTABBAR_MULTILINE)
		.value("VIEW_DOCCHANGEMARGIN", NPPIDM_VIEW_DOCCHANGEMARGIN)
		.value("VIEW_FOLD", NPPIDM_VIEW_FOLD)
		.value("VIEW_FOLD_1", NPPIDM_VIEW_FOLD_1)
		.value("VIEW_FOLD_2", NPPIDM_VIEW_FOLD_2)
		.value("VIEW_FOLD_3", NPPIDM_VIEW_FOLD_3)
		.value("VIEW_FOLD_4", NPPIDM_VIEW_FOLD_4)
		.value("VIEW_FOLD_5", NPPIDM_VIEW_FOLD_5)
		.value("VIEW_FOLD_6", NPPIDM_VIEW_FOLD_6)
		.value("VIEW_FOLD_7", NPPIDM_VIEW_FOLD_7)
		.value("VIEW_FOLD_8", NPPIDM_VIEW_FOLD_8)
		.value("VIEW_UNFOLD", NPPIDM_VIEW_UNFOLD)
		.value("VIEW_UNFOLD_1", NPPIDM_VIEW_UNFOLD_1)
		.value("VIEW_UNFOLD_2", NPPIDM_VIEW_UNFOLD_2)
		.value("VIEW_UNFOLD_3", NPPIDM_VIEW_UNFOLD_3)
		.value("VIEW_UNFOLD_4", NPPIDM_VIEW_UNFOLD_4)
		.value("VIEW_UNFOLD_5", NPPIDM_VIEW_UNFOLD_5)
		.value("VIEW_UNFOLD_6", NPPIDM_VIEW_UNFOLD_6)
		.value("VIEW_UNFOLD_7", NPPIDM_VIEW_UNFOLD_7)
		.value("VIEW_UNFOLD_8", NPPIDM_VIEW_UNFOLD_8)
		.value("VIEW_GOTO_ANOTHER_VIEW", NPPIDM_VIEW_GOTO_ANOTHER_VIEW)
		.value("VIEW_CLONE_TO_ANOTHER_VIEW", NPPIDM_VIEW_CLONE_TO_ANOTHER_VIEW)
		.value("VIEW_GOTO_NEW_INSTANCE", NPPIDM_VIEW_GOTO_NEW_INSTANCE)
		.value("VIEW_LOAD_IN_NEW_INSTANCE", NPPIDM_VIEW_LOAD_IN_NEW_INSTANCE)
		.value("VIEW_SWITCHTO_OTHER_VIEW", NPPIDM_VIEW_SWITCHTO_OTHER_VIEW)
		.value("FORMAT_TODOS", NPPIDM_FORMAT_TODOS)
		.value("FORMAT_TOUNIX", NPPIDM_FORMAT_TOUNIX)
		.value("FORMAT_TOMAC", NPPIDM_FORMAT_TOMAC)
		.value("FORMAT_ANSI", NPPIDM_FORMAT_ANSI)
		.value("FORMAT_UTF_8", NPPIDM_FORMAT_UTF_8)
		.value("FORMAT_UCS_2BE", NPPIDM_FORMAT_UCS_2BE)
		.value("FORMAT_UCS_2LE", NPPIDM_FORMAT_UCS_2LE)
		.value("FORMAT_AS_UTF_8", NPPIDM_FORMAT_AS_UTF_8)
		.value("FORMAT_CONV2_ANSI", NPPIDM_FORMAT_CONV2_ANSI)
		.value("FORMAT_CONV2_AS_UTF_8", NPPIDM_FORMAT_CONV2_AS_UTF_8)
		.value("FORMAT_CONV2_UTF_8", NPPIDM_FORMAT_CONV2_UTF_8)
		.value("FORMAT_CONV2_UCS_2BE", NPPIDM_FORMAT_CONV2_UCS_2BE)
		.value("FORMAT_CONV2_UCS_2LE", NPPIDM_FORMAT_CONV2_UCS_2LE)
		.value("FORMAT_ENCODE", NPPIDM_FORMAT_ENCODE)
		.value("FORMAT_WIN_1250", NPPIDM_FORMAT_WIN_1250)
		.value("FORMAT_WIN_1251", NPPIDM_FORMAT_WIN_1251)
		.value("FORMAT_WIN_1252", NPPIDM_FORMAT_WIN_1252)
		.value("FORMAT_WIN_1253", NPPIDM_FORMAT_WIN_1253)
		.value("FORMAT_WIN_1254", NPPIDM_FORMAT_WIN_1254)
		.value("FORMAT_WIN_1255", NPPIDM_FORMAT_WIN_1255)
		.value("FORMAT_WIN_1256", NPPIDM_FORMAT_WIN_1256)
		.value("FORMAT_WIN_1257", NPPIDM_FORMAT_WIN_1257)
		.value("FORMAT_WIN_1258", NPPIDM_FORMAT_WIN_1258)
		.value("FORMAT_ISO_8859_1", NPPIDM_FORMAT_ISO_8859_1)
		.value("FORMAT_ISO_8859_2", NPPIDM_FORMAT_ISO_8859_2)
		.value("FORMAT_ISO_8859_3", NPPIDM_FORMAT_ISO_8859_3)
		.value("FORMAT_ISO_8859_4", NPPIDM_FORMAT_ISO_8859_4)
		.value("FORMAT_ISO_8859_5", NPPIDM_FORMAT_ISO_8859_5)
		.value("FORMAT_ISO_8859_6", NPPIDM_FORMAT_ISO_8859_6)
		.value("FORMAT_ISO_8859_7", NPPIDM_FORMAT_ISO_8859_7)
		.value("FORMAT_ISO_8859_8", NPPIDM_FORMAT_ISO_8859_8)
		.value("FORMAT_ISO_8859_9", NPPIDM_FORMAT_ISO_8859_9)
		.value("FORMAT_ISO_8859_10", NPPIDM_FORMAT_ISO_8859_10)
		.value("FORMAT_ISO_8859_11", NPPIDM_FORMAT_ISO_8859_11)
		.value("FORMAT_ISO_8859_13", NPPIDM_FORMAT_ISO_8859_13)
		.value("FORMAT_ISO_8859_14", NPPIDM_FORMAT_ISO_8859_14)
		.value("FORMAT_ISO_8859_15", NPPIDM_FORMAT_ISO_8859_15)
		.value("FORMAT_ISO_8859_16", NPPIDM_FORMAT_ISO_8859_16)
		.value("FORMAT_DOS_437", NPPIDM_FORMAT_DOS_437)
		.value("FORMAT_DOS_720", NPPIDM_FORMAT_DOS_720)
		.value("FORMAT_DOS_737", NPPIDM_FORMAT_DOS_737)
		.value("FORMAT_DOS_775", NPPIDM_FORMAT_DOS_775)
		.value("FORMAT_DOS_850", NPPIDM_FORMAT_DOS_850)
		.value("FORMAT_DOS_852", NPPIDM_FORMAT_DOS_852)
		.value("FORMAT_DOS_855", NPPIDM_FORMAT_DOS_855)
		.value("FORMAT_DOS_857", NPPIDM_FORMAT_DOS_857)
		.value("FORMAT_DOS_858", NPPIDM_FORMAT_DOS_858)
		.value("FORMAT_DOS_860", NPPIDM_FORMAT_DOS_860)
		.value("FORMAT_DOS_861", NPPIDM_FORMAT_DOS_861)
		.value("FORMAT_DOS_862", NPPIDM_FORMAT_DOS_862)
		.value("FORMAT_DOS_863", NPPIDM_FORMAT_DOS_863)
		.value("FORMAT_DOS_865", NPPIDM_FORMAT_DOS_865)
		.value("FORMAT_DOS_866", NPPIDM_FORMAT_DOS_866)
		.value("FORMAT_DOS_869", NPPIDM_FORMAT_DOS_869)
		.value("FORMAT_BIG5", NPPIDM_FORMAT_BIG5)
		.value("FORMAT_GB2312", NPPIDM_FORMAT_GB2312)
		.value("FORMAT_SHIFT_JIS", NPPIDM_FORMAT_SHIFT_JIS)
		.value("FORMAT_KOREAN_WIN", NPPIDM_FORMAT_KOREAN_WIN)
		.value("FORMAT_EUC_KR", NPPIDM_FORMAT_EUC_KR)
		.value("FORMAT_TIS_620", NPPIDM_FORMAT_TIS_620)
		.value("FORMAT_MAC_CYRILLIC", NPPIDM_FORMAT_MAC_CYRILLIC)
		.value("FORMAT_KOI8U_CYRILLIC", NPPIDM_FORMAT_KOI8U_CYRILLIC)
		.value("FORMAT_KOI8R_CYRILLIC", NPPIDM_FORMAT_KOI8R_CYRILLIC)
		.value("FORMAT_ENCODE_END", NPPIDM_FORMAT_ENCODE_END)
		.value("LANGSTYLE_CONFIG_DLG", NPPIDM_LANGSTYLE_CONFIG_DLG)
		.value("LANG_C", NPPIDM_LANG_C)
		.value("LANG_CPP", NPPIDM_LANG_CPP)
		.value("LANG_JAVA", NPPIDM_LANG_JAVA)
		.value("LANG_HTML", NPPIDM_LANG_HTML)
		.value("LANG_XML", NPPIDM_LANG_XML)
		.value("LANG_JS", NPPIDM_LANG_JS)
		.value("LANG_PHP", NPPIDM_LANG_PHP)
		.value("LANG_ASP", NPPIDM_LANG_ASP)
		.value("LANG_CSS", NPPIDM_LANG_CSS)
		.value("LANG_PASCAL", NPPIDM_LANG_PASCAL)
		.value("LANG_PYTHON", NPPIDM_LANG_PYTHON)
		.value("LANG_PERL", NPPIDM_LANG_PERL)
		.value("LANG_OBJC", NPPIDM_LANG_OBJC)
		.value("LANG_ASCII", NPPIDM_LANG_ASCII)
		.value("LANG_TEXT", NPPIDM_LANG_TEXT)
		.value("LANG_RC", NPPIDM_LANG_RC)
		.value("LANG_MAKEFILE", NPPIDM_LANG_MAKEFILE)
		.value("LANG_INI", NPPIDM_LANG_INI)
		.value("LANG_SQL", NPPIDM_LANG_SQL)
		.value("LANG_VB", NPPIDM_LANG_VB)
		.value("LANG_BATCH", NPPIDM_LANG_BATCH)
		.value("LANG_CS", NPPIDM_LANG_CS)
		.value("LANG_LUA", NPPIDM_LANG_LUA)
		.value("LANG_TEX", NPPIDM_LANG_TEX)
		.value("LANG_FORTRAN", NPPIDM_LANG_FORTRAN)
		.value("LANG_BASH", NPPIDM_LANG_BASH)
		.value("LANG_FLASH", NPPIDM_LANG_FLASH)
		.value("LANG_NSIS", NPPIDM_LANG_NSIS)
		.value("LANG_TCL", NPPIDM_LANG_TCL)
		.value("LANG_LISP", NPPIDM_LANG_LISP)
		.value("LANG_SCHEME", NPPIDM_LANG_SCHEME)
		.value("LANG_ASM", NPPIDM_LANG_ASM)
		.value("LANG_DIFF", NPPIDM_LANG_DIFF)
		.value("LANG_PROPS", NPPIDM_LANG_PROPS)
		.value("LANG_PS", NPPIDM_LANG_PS)
		.value("LANG_RUBY", NPPIDM_LANG_RUBY)
		.value("LANG_SMALLTALK", NPPIDM_LANG_SMALLTALK)
		.value("LANG_VHDL", NPPIDM_LANG_VHDL)
		.value("LANG_CAML", NPPIDM_LANG_CAML)
		.value("LANG_KIX", NPPIDM_LANG_KIX)
		.value("LANG_ADA", NPPIDM_LANG_ADA)
		.value("LANG_VERILOG", NPPIDM_LANG_VERILOG)
		.value("LANG_AU3", NPPIDM_LANG_AU3)
		.value("LANG_MATLAB", NPPIDM_LANG_MATLAB)
		.value("LANG_HASKELL", NPPIDM_LANG_HASKELL)
		.value("LANG_INNO", NPPIDM_LANG_INNO)
		.value("LANG_CMAKE", NPPIDM_LANG_CMAKE)
		.value("LANG_YAML", NPPIDM_LANG_YAML)
		.value("LANG_COBOL", NPPIDM_LANG_COBOL)
		.value("LANG_D", NPPIDM_LANG_D)
		.value("LANG_GUI4CLI", NPPIDM_LANG_GUI4CLI)
		.value("LANG_POWERSHELL", NPPIDM_LANG_POWERSHELL)
		.value("LANG_R", NPPIDM_LANG_R)
		.value("LANG_JSP", NPPIDM_LANG_JSP)
		.value("LANG_EXTERNAL", NPPIDM_LANG_EXTERNAL)
		.value("LANG_EXTERNAL_LIMIT", NPPIDM_LANG_EXTERNAL_LIMIT)
		.value("LANG_USER", NPPIDM_LANG_USER)
		.value("LANG_USER_LIMIT", NPPIDM_LANG_USER_LIMIT)
		.value("HOMESWEETHOME", NPPIDM_HOMESWEETHOME)
		.value("PROJECTPAGE", NPPIDM_PROJECTPAGE)
		.value("ONLINEHELP", NPPIDM_ONLINEHELP)
		.value("FORUM", NPPIDM_FORUM)
		.value("PLUGINSHOME", NPPIDM_PLUGINSHOME)
		.value("UPDATE_NPP", NPPIDM_UPDATE_NPP)
		.value("WIKIFAQ", NPPIDM_WIKIFAQ)
		.value("HELP", NPPIDM_HELP)
		.value("SETTING_TAB_SIZE", NPPIDM_SETTING_TAB_SIZE)
		.value("SETTING_TAB_REPLCESPACE", NPPIDM_SETTING_TAB_REPLCESPACE)
		.value("SETTING_HISTORY_SIZE", NPPIDM_SETTING_HISTORY_SIZE)
		.value("SETTING_EDGE_SIZE", NPPIDM_SETTING_EDGE_SIZE)
		.value("SETTING_IMPORTPLUGIN", NPPIDM_SETTING_IMPORTPLUGIN)
		.value("SETTING_IMPORTSTYLETHEMS", NPPIDM_SETTING_IMPORTSTYLETHEMS)
		.value("SETTING_TRAYICON", NPPIDM_SETTING_TRAYICON)
		.value("SETTING_SHORTCUT_MAPPER", NPPIDM_SETTING_SHORTCUT_MAPPER)
		.value("SETTING_REMEMBER_LAST_SESSION", NPPIDM_SETTING_REMEMBER_LAST_SESSION)
		.value("SETTING_PREFERECE", NPPIDM_SETTING_PREFERECE)
		.value("SETTING_AUTOCNBCHAR", NPPIDM_SETTING_AUTOCNBCHAR)
		.value("SYSTRAYPOPUP_ACTIVATE", NPPIDM_SYSTRAYPOPUP_ACTIVATE)
		.value("SYSTRAYPOPUP_NEWDOC", NPPIDM_SYSTRAYPOPUP_NEWDOC)
		.value("SYSTRAYPOPUP_NEW_AND_PASTE", NPPIDM_SYSTRAYPOPUP_NEW_AND_PASTE)
		.value("SYSTRAYPOPUP_OPENFILE", NPPIDM_SYSTRAYPOPUP_OPENFILE)
		.value("SYSTRAYPOPUP_CLOSE", NPPIDM_SYSTRAYPOPUP_CLOSE);

	//lint +e1793

}

}
