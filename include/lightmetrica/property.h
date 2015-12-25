/*
    Lightmetrica - A modern, research-oriented renderer

    Copyright (c) 2015 Hisanari Otsu

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#pragma once

#include <lightmetrica/component.h>

LM_NAMESPACE_BEGIN

enum class PropertyNodeType : int
{
    Null,
    Scalar,
    Sequence,
    Map,
    Undefined,
};

/*!
    Property node.

    An element of the property.
*/
class PropertyNode : public Component
{
public:

    LM_INTERFACE_CLASS(PropertyNode, Component);

public:

    PropertyNode() = default;
    LM_DISABLE_COPY_AND_MOVE(PropertyNode);

public:

    /*!
        Type of the node.
    */
    LM_INTERFACE_F(Type, PropertyNodeType());

    /*!
        Key of the node.
        Only available for `Map` type.
    */
    LM_INTERFACE_F(Key, std::string());

    /*!
        Scalar value of the node.
        Only available for `Scalar` type.
    */
    LM_INTERFACE_F(Scalar, std::string());

    /*!
        Get a number of child elements.
        Only available for `Sequence` type.
    */
    LM_INTERFACE_F(Size, int());

    /*!
        Find a child by name.
        Only available for `Map` type.
    */
    LM_INTERFACE_F(Child, const PropertyNode*(const std::string&));

    /*!
        Get a child by index.
        Only available for `Sequence` type.
    */
    LM_INTERFACE_F(At, const PropertyNode*(int));

public:

    template <typename T> auto As() const -> T;
    template <> auto As<std::string>() const -> std::string { return Scalar(); }
    template <> auto As<int>() const -> int { return std::stoi(Scalar()); }
    template <> auto As<double>() const -> double { return std::stod(Scalar()); }

};

/*!
    Property tree.
    
    Manages tree structure.
    Mainly utilized as asset parameters.
    This class manages all instances of the property nodes.
*/
class PropertyTree : public Component
{
public:

    LM_INTERFACE_CLASS(PropertyTree, Component);

public:

    PropertyTree() = default;
    LM_DISABLE_COPY_AND_MOVE(PropertyTree);

public:
    
    /*!
        Load property from YAML sequences.
    */
    LM_INTERFACE_F(LoadFromString, bool(const std::string&));

    /*!
        Get root node.
    */
    LM_INTERFACE_F(Root, const PropertyNode*());

};

LM_NAMESPACE_END