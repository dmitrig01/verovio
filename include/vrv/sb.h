/////////////////////////////////////////////////////////////////////////////
// Name:        sb.h
// Author:      Klaus Rettinghaus
// Created:     2018
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#ifndef __VRV_SB_H__
#define __VRV_SB_H__

#include "atts_shared.h"
#include "facsimileinterface.h"
#include "systemelement.h"

namespace vrv {

//----------------------------------------------------------------------------
// Sb
//----------------------------------------------------------------------------

/**
 * This class represents a MEI sb in score-based MEI.
 * In page-based MEI, it remains as it is. Actual systems are represented by System objects.
 */
class Sb : public SystemElement, public FacsimileInterface, public AttNNumberLike {
public:
    /**
     * @name Constructors, destructors, and other standard methods
     * Reset method resets all attribute classes
     */
    ///@{
    Sb();
    virtual ~Sb();
    Object *Clone() const override { return new Sb(*this); }
    void Reset() override;
    std::string GetClassName() const override { return "sb"; }
    ///@}

    /**
     * @name Getter to interfaces
     */
    ///@{
    FacsimileInterface *GetFacsimileInterface() override { return vrv_cast<FacsimileInterface *>(this); }
    const FacsimileInterface *GetFacsimileInterface() const override
    {
        return vrv_cast<const FacsimileInterface *>(this);
    }

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

private:
    //
public:
    /**
     * System left and right margins (MusicXML print/system-layout/system-margins) carried over from import
     * so that they can be transferred to the System object created from this Sb during cast off.
     * Left as VRV_UNSET when not read from the MusicXML source.
     */
    ///@{
    int m_systemLeftMar = VRV_UNSET;
    int m_systemRightMar = VRV_UNSET;
    ///@}

    /**
     * Flag indicating that the system started by this <sb> should never be stretched by horizontal
     * justification (i.e., it is rendered at its natural content width). Carried over from import (see
     * MusicXmlInput::ReadMusicXmlPrint) so that it can be transferred to the System object created from
     * this Sb during cast off (see CastOffEncodingFunctor::VisitSb).
     */
    bool m_noJustify = false;

    /**
     * Vertical distance from the previous system (MusicXML print/system-layout/system-distance), in the
     * same DEFINITION_FACTOR-scaled "vu" convention as m_systemLeftMar/m_systemRightMar. Can be negative
     * (pulling two systems closer together, even overlapping). Carried over from import (see
     * MusicXmlInput::ReadMusicXmlPrint) so that it can be transferred to the System object created from
     * this Sb during cast off (see CastOffEncodingFunctor::VisitSb). Left as VRV_UNSET when not read from
     * the MusicXML source, in which case normal automatic system spacing applies.
     */
    int m_systemDistance = VRV_UNSET;

private:
    //
};

} // namespace vrv

#endif
