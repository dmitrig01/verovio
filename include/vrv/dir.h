/////////////////////////////////////////////////////////////////////////////
// Name:        dir.h
// Author:      Laurent Pugin
// Created:     2016
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#ifndef __VRV_DIR_H__
#define __VRV_DIR_H__

#include "controlelement.h"
#include "textdirinterface.h"
#include "timeinterface.h"

namespace vrv {

class TextElement;

//----------------------------------------------------------------------------
// Dir (directive)
//----------------------------------------------------------------------------

/**
 * This class models the MEI <dir> element.
 */
class Dir : public ControlElement,
            public TextListInterface,
            public TextDirInterface,
            public TimeSpanningInterface,
            public AttExtender,
            public AttLang,
            public AttLineRendBase,
            public AttVerticalGroup {
public:
    /**
     * @name Constructors, destructors, and other standard methods
     * Reset method reset all attribute classes
     */
    ///@{
    Dir();
    virtual ~Dir();
    Object *Clone() const override { return new Dir(*this); }
    void Reset() override;
    std::string GetClassName() const override { return "dir"; }
    ///@}

    /**
     * @name Getter to interfaces
     */
    ///@{
    TextDirInterface *GetTextDirInterface() override { return vrv_cast<TextDirInterface *>(this); }
    const TextDirInterface *GetTextDirInterface() const override { return vrv_cast<const TextDirInterface *>(this); }
    TimePointInterface *GetTimePointInterface() override { return vrv_cast<TimePointInterface *>(this); }
    const TimePointInterface *GetTimePointInterface() const override
    {
        return vrv_cast<const TimePointInterface *>(this);
    }
    TimeSpanningInterface *GetTimeSpanningInterface() override { return vrv_cast<TimeSpanningInterface *>(this); }
    const TimeSpanningInterface *GetTimeSpanningInterface() const override
    {
        return vrv_cast<const TimeSpanningInterface *>(this);
    }
    ///@}

    /**
     * Add an element (text, rend. etc.) to a dir.
     * Only supported elements will be actually added to the child list.
     */
    bool IsSupportedChild(ClassId classId) override;

    /**
     * See FloatingObject::IsExtenderElement
     */
    bool IsExtenderElement() const override { return GetExtender() == BOOLEAN_true; }

    //----------//
    // Functors //
    //----------//

    /**
     * Interface for class functor visitation
     */
    ///@{
    FunctorCode Accept(Functor &functor) override;
    FunctorCode Accept(ConstFunctor &functor) const override;
    FunctorCode AcceptEnd(Functor &functor) override;
    FunctorCode AcceptEnd(ConstFunctor &functor) const override;
    ///@}

protected:
    //
private:
    //
public:
    /**
     * Additional vertical offset (in internal drawing units scaled by DEFINITION_FACTOR, i.e. the same
     * convention as System::m_systemLeftMar/m_systemRightMar and Tempo::m_drawingYOffset) carried over
     * from a MusicXML direction/direction-type/words default-y and relative-y attribute. Applied on top of
     * the automatically computed distance from the staff so that a plain directive's vertical position can
     * be nudged, independent of and in addition to @vgrp (which is a grouping/equalization id, not a
     * position - see MusicXmlInput::ReadMusicXmlDirection). Zero (the default) means no adjustment.
     */
    int m_drawingYOffset = 0;

private:
    //
};

} // namespace vrv

#endif
