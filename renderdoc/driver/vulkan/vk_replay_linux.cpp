/******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2015 Vulkan
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

#include "vk_replay.h"

void VulkanReplay::OutputWindow::SetWindowHandle(void *wn)
{
	void **displayAndDrawable = (void **)wn;

	connection = (xcb_connection_t *)displayAndDrawable[0];
	screen = (xcb_screen_t *)displayAndDrawable[1];
	wnd = (xcb_window_t)(size_t)displayAndDrawable[2];
}

void VulkanReplay::GetOutputWindowDimensions(uint64_t id, int32_t &w, int32_t &h)
{
	if(id == 0 || m_OutputWindows.find(id) == m_OutputWindows.end())
		return;
	
	OutputWindow &outw = m_OutputWindows[id];
	
	xcb_get_geometry_cookie_t  geomCookie = xcb_get_geometry (outw.connection, outw.wnd);  // window is a xcb_drawable_t
	xcb_get_geometry_reply_t  *geom       = xcb_get_geometry_reply (outw.connection, geomCookie, NULL);

	w = (int32_t)geom->width;
	h = (int32_t)geom->height;

	free(geom);
}

bool VulkanReplay::IsOutputWindowVisible(uint64_t id)
{
	if(id == 0 || m_OutputWindows.find(id) == m_OutputWindows.end())
		return false;

	VULKANNOTIMP("Optimisation missing - output window always returning true");

	return true;
}