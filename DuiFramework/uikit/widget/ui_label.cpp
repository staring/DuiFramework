﻿#include "stdafx.h"
#include "ui_label.h"
#include "uikit/render/ui_render_engine.h"

namespace ui
{
	UILabel::UILabel()
		: font_(UIFont::CreateDefault())
	{

	}

	UILabel::~UILabel()
	{

	}

	void UILabel::setText(const std::wstring& text)
	{
		if (text_ == text)
			return;
		text_ = text;
		needsTextLayout_ = true;
		SchedulePaint();
	}


// 	void UILabel::setAttributeString(UIAttributeString* attributeString)
// 	{
// 		attributeString_.reset(attributeString);
// 		needsTextLayout_ = true;
// 		SchedulePaint();
// 	}


	void UILabel::setFont(UIFont* font)
	{
		if (font->IsEqual(font_))
			return;

		font_.reset(font);
		needsTextLayout_ = true;
		SchedulePaint();
	}

	void UILabel::setTextColor(Color color)
	{
		if (textColor_ == color)
			return;

		textColor_ = color;
		SchedulePaint();
	}

	void UILabel::OnPaint(UIRenderContext* painter)
	{
		if (background_color_ != Color_Transparent)
			painter->FillRect(GetLocalBounds(), background_color_);

		layoutText();
		drawTextInRect(painter, textRectCached_);
	}

	void UILabel::setTextAlignment(TextAlignment v)
	{
		if (textAlignment_ == v)
			return;
		textAlignment_ = v;
		needsTextLayout_ = true;
		SchedulePaint();
	}

	void UILabel::setVerticalAlignment(VerticalAlignment v)
	{
		if (verticalAligment_ == v)
			return;
		verticalAligment_ = v;
		needsTextLayout_ = true;
		SchedulePaint();
	}


// 	void UILabel::setLineBreakMode(UILineBreakMode v)
// 	{
// 		if (lineBreakMode_ == v)
// 			return;
// 		lineBreakMode_ = v;
// 		needsTextLayout_ = true;
// 	}


	Rect UILabel::textRectForBounds(const Rect& boundsRect)
	{
		int width = font_->renderFont()->MeasureWidth(text_.c_str(), text_.size());
		int height = font_->renderFont()->GetHeight();
		Rect textRect(boundsRect.x(), boundsRect.y(), width, height);
		if (!(textAlignment_ == TextAlignmentLeft || textRect.width() == boundsRect.width()))
		{
			int delta = boundsRect.width() - textRect.width();
			if (textAlignment_ == TextAlignmentCenter) {
				textRect.Offset(delta / 2, 0);
			}
			else { // TextAlignmentRight
				textRect.Offset(delta, 0);
			}
		}

		if (!(verticalAligment_ == VerticalAlignmentTop || textRect.height() == boundsRect.height()))
		{
			int delta = boundsRect.height() - textRect.height();
			if (verticalAligment_ == VerticalAlignmentMiddle) {
				textRect.Offset(0, delta / 2);
			}
			else { // VerticalAlignmentBottom
				textRect.Offset(0, delta);
			}
		}
		return textRect;
	}

	void UILabel::drawTextInRect(UIRenderContext* painter, const Rect& rect)
	{
		UIScopedPainter helper(painter, Matrix(1.0, 0, 0, 1.0, rect.x(), rect.y()));
		painter->DrawText(text_, font_, textColor_);
// 		UIGlyph* glyphs = NULL;
// 		size_t glyphsCount = 0;
// 		scoped_refptr<UIRenderFont> font = font_->renderFont();
// 		font->GetGlyphs(text_.c_str(), text_.size(), &glyphs, glyphsCount);
// 		painter->ShowGlyphs(glyphs, glyphsCount, font, textColor_);
	}

	void UILabel::layoutText()
	{
		if (!needsTextLayout_)
			return;

		needsTextLayout_ = false;
		Rect rect = textRectForBounds(GetLocalBounds());
		if (rect == textRectCached_)
			return;
		textRectCached_ = rect;
		SchedulePaint();
	}

	const std::wstring& UILabel::text() const
	{
		return text_;
	}

}