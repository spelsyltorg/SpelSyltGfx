#include "GfxInclude.h"
#include "OpenGL.h"

void SSGFX::SetScreenAsRenderTarget()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
