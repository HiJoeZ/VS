#pragma once

#ifdef DEBUG_
#define GL_CALL(func) func;checkError();
#else
#define GL_CALL(func) func;
#endif

void checkError();