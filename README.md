To use: 

  Eve (Roomba interface)
  Import EdenCommon UserOS.h & Backend.h
  Import Eve Backend.h (Overrides Eden backend)
  Run.cpp is the entry point.
  
  Adam (Wombat interface)
  Import EdenCommon UserOS.h & Backend.h
  Import Adam Backend.h (Overrides Eden backend)
  Run.cpp is the entry point.
Backend is complicated and annoying and technical. for most users, the UserOS abstraction layer should be suffice. Despite this, the backend classes are public and usable, even if not recommended.
