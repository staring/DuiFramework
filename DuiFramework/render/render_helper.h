#pragma once
#include "render/render_context.h"

namespace ui
{
	class ScopedPainter
	{
	public:
		ScopedPainter(RenderContext* painter, const Matrix& m);
		~ScopedPainter();
	private:
		Matrix m_;
		RenderContext* p_;
	};

	class ScopedClipper
	{
	public:
		ScopedClipper(RenderContext* painter, const Rect& r);
		ScopedClipper(RenderContext* painter, const RenderPath* r);
		~ScopedClipper();
	private:
		RenderContext* p_;
	};
}