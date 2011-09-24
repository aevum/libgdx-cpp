/*
 *  Copyright 2011 Aevum Software aevum @ aevumlab.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 *  @author Ozires Bortolon de Faria ozires@aevumlab.com
 *  @author aevum team
 */

#include "SvgParser.hpp"
#include <stdexcept>
#include "gdx-cpp/math/Matrix3.hpp"
#include <string.h>
#include <cassert>
#include <algorithm>
#include "gdx-cpp/math/MathUtils.hpp"
#include "gdx-cpp/utils/StringConvertion.hpp"

using namespace gdx_cpp::graphics::g2d::svg;
using namespace gdx_cpp::utils;

gdx_cpp::graphics::g2d::svg::SvgParser::SvgParser(SvgPixmapInterface& iface)
        : pixmap(iface)
{
}

void SvgParser::render(gdx_cpp::utils::XmlReader::Element* const svg)
{
    beginElement(svg);

    for (int i = 0; i < svg->getChildCount(); ++i) {
        render(svg->getChild(i));
    }

    endElement(svg);
}

void SvgParser::beginElement(XmlReader::Element* const currentNode)
{
    std::string name = currentNode->getName();

    if (name == "title")
    {
        m_titleFlag = true;
    }
    else if (name == "g")
    {
        pixmap.begin();
        parse_attr(currentNode);
    }
    else if (name == "path")
    {
        if (m_pathFlag)
        {
            throw std::runtime_error("start_element: Nested path");
        }

        pixmap.beginPath();
        parse_path(currentNode);
        pixmap.endPath();
        m_pathFlag = true;
    }
    else if (name == "rect")
    {
        parse_rect(currentNode);
    }
    else if (name == "line")
    {
        parse_line(currentNode);
    }
    else if (name == "polyline")
    {
        parse_poly(currentNode, false);
    }
    else if (name == "polygon")
    {
        parse_poly(currentNode, true);
    }
}

void SvgParser::endElement(utils::XmlReader::Element* currentNode)
{
    std::string name = currentNode->getName();

    if (name == "title")
    {
        m_titleFlag = false;
    }
    else if (name == "g")
    {
        pixmap.end();
    }
    else if (name == "path")
    {
        m_pathFlag = false;
    }
}

void gdx_cpp::graphics::g2d::svg::SvgParser::parse_attr(gdx_cpp::utils::XmlReader::Element* node)
{
    XmlReader::Element::AttributesMap::const_iterator it = node->getAttributesBegin();
    XmlReader::Element::AttributesMap::const_iterator end = node->getAttributesEnd();

    for (; it != end; ++it) {
        if (it->first == "style") {
            parse_style(it->second);
        } else {
            parse_attr(it->first, it->second);
        }
    }
}

void gdx_cpp::graphics::g2d::svg::SvgParser::parse_style(const std::string& style)
{
    std::string::size_type pos = 0, found = 0;

    while ((found = style.find(";", pos)) != std::string::npos)
    {
        std::string namedValue = style.substr(pos, found - pos);
        std::string::size_type comma = namedValue.find(":");
        std::string name = namedValue.substr(0, comma);
        std::string value = namedValue.substr(comma, namedValue.length());

        std::remove(name.begin(),name.end(), ' ');
        std::remove(value.begin(),name.end(), ' ');
        parse_attr(name, value);

        pos = found;
    }
}

bool gdx_cpp::graphics::g2d::svg::SvgParser::parse_attr(const std::string& name, const std::string& value)
{
    if (name == "style")
    {
        parse_style(value);
    }
    else if (name == "fill")
    {
        if (value == "none")
        {
            pixmap.fillNone();
        }
        else
        {
            pixmap.fill(parse_color(value));
        }
    }
    else if (name == "fill-opacity")
    {
        pixmap.fillOpacity(utils::from_string<double>(value));
    }
    else  if (name == "stroke")
    {
        if (value == "none")
        {
            pixmap.strokeNone();
        }
        else
        {
            pixmap.stroke(parse_color(value));
        }
    }
    else if (name == "stroke-width")
    {
        pixmap.setStrokeWidth(utils::from_string<double>(value));
    }
    else if (name == "stroke-linecap")
    {
        if (value == "butt")        pixmap.setLineCap(SvgPixmapInterface::ButtLineCap);
        else if (value == "round")  pixmap.setLineCap(SvgPixmapInterface::RoundLineCap);
        else if (value == "square") pixmap.setLineCap(SvgPixmapInterface::SquareLineCap);
    }
    else if (name == "stroke-linejoin")
    {
        if (value == "miter")      pixmap.setLineJoin(SvgPixmapInterface::MiterJoin);
        else if (value == "round") pixmap.setLineJoin(SvgPixmapInterface::RoundJoin);
        else if (value == "bevel") pixmap.setLineJoin(SvgPixmapInterface::BevelJoin);
    }
    else if (name == "stroke-miterlimit")
    {
        pixmap.setMiterLimit(utils::from_string<double>(value));
    }
    else if (name == "stroke-opacity")
    {
        pixmap.setStrokeOpacity(utils::from_string<double>(value));
    }
    else if (name == "transform")
    {
        parse_transform(value);
    }
    //else
    //if(strcmp(el, "<OTHER_ATTRIBUTES>") == 0)
    //{
    //}
    // . . .
    else
    {
        return false;
    }
    return true;
}

void gdx_cpp::graphics::g2d::svg::SvgParser::parse_transform(const std::string& transform)
{
    std::string::size_type pos = 0, last = 0;

    while (pos != std::string::npos) {
        if ((pos = transform.find("matrix", last)) != std::string::npos) {
            parse_matrix(transform.substr(last, pos));
        } else if ((pos = transform.find("translate", last)) != std::string::npos) {
            parse_translate(transform.substr(last, pos));
        } else if ((pos = transform.find("rotate", last)) != std::string::npos) {
            parse_rotate(transform.substr(last, pos));
        } else if ((pos = transform.find("scale", last)) != std::string::npos) {
            parse_scale(transform.substr(last, pos));
        } else if ((pos = transform.find("skewX", last)) != std::string::npos) {
            parse_skew_x(transform.substr(last, pos));
        } else if ((pos = transform.find("skewY", last)) != std::string::npos) {
            parse_skew_y(transform.substr(last, pos));
        } else {
            pos++;
        }

        last = pos;
    }
}

///splits the items inside argument calls like transform(129.2, 44)
template <typename T>
std::vector<T> splitArgs(const std::string& item, const char* delim) {
    std::string::size_type pos = item.find("("), last = pos;
    std::vector<T> result;

    while ((pos = item.find(delim, last)) != std::string::npos ||
            (pos = item.find(")", last)) != std::string::npos) {
        result.push_back(gdx_cpp::utils::from_string<T>(item.substr(last, last - pos)));
    }

    return result;
}

void gdx_cpp::graphics::g2d::svg::SvgParser::parse_matrix(std::string matrixArgs)
{
    std::vector<float> res = splitArgs<float>(matrixArgs, ",");

    assert(res.size() == 6);

    pixmap.transAffine(res);
}

void gdx_cpp::graphics::g2d::svg::SvgParser::parse_rotate(std::string rotateArgs)
{
    std::vector<float> res = splitArgs<float>(rotateArgs, ",");

    if (res.size() == 1) {
        pixmap.setRotation(math::utils::toRadians(res[0]));
    } else if (res.size() == 3) {
        pixmap.setRotationTranslation(math::utils::toRadians(res[0]), res[1], res[2]);
    } else {
        throw std::runtime_error("SvgParser::parse_rotate: invalid number of arguments");
    }
}

void gdx_cpp::graphics::g2d::svg::SvgParser::parse_scale(std::string scaleArgs)
{
    std::vector<float> res = splitArgs<float>(scaleArgs, ",");

    assert(res.size() >= 1);

    if (res.size() == 1) {
        res.push_back(res[0]);
    }

    pixmap.setScaling(res[0], res[1]);
}

void gdx_cpp::graphics::g2d::svg::SvgParser::parse_skew_x(std::string skewXargs)
{
    std::vector<float> res = splitArgs<float>(skewXargs, ",");

    assert(res.size() == 1);

    pixmap.setSkew(res[0], 0.0f);
}

void gdx_cpp::graphics::g2d::svg::SvgParser::parse_skew_y(std::string skewYargs)
{
    std::vector<float> res = splitArgs<float>(skewYargs, ",");

    assert(res.size() == 1);

    pixmap.setSkew( 0.0f, res[0]);
}

void gdx_cpp::graphics::g2d::svg::SvgParser::parse_translate(std::string translateArgs)
{
    std::vector<float> res = splitArgs<float>(translateArgs, ",");

    assert(res.size() >= 1);
    if (res.size() == 1) res.push_back(0);

    pixmap.setTranslation(res[0], res[1]);
}

gdx_cpp::graphics::Color gdx_cpp::graphics::g2d::svg::SvgParser::parse_color(const std::string& colorValue)
{
    std::string::size_type pos = colorValue.find("#");

    if (pos != std::string::npos) {
        return graphics::Color::fromRgb(from_string< unsigned int >(colorValue.substr(pos, pos - colorValue.length())));
    } else if ((pos = colorValue.find("rgb")) != std::string::npos) {
        throw std::runtime_error("No implemented yet");
    } else {
        throw std::runtime_error("No implemented yet");
    }
}

void gdx_cpp::graphics::g2d::svg::SvgParser::parse_line(gdx_cpp::utils::XmlReader::Element* node)
{
    pixmap.beginPath();

    parse_attr(node);

    pixmap.moveTo(utils::from_string<float>(node->getAttribute("x1")),
                  utils::from_string<float>(node->getAttribute("y1")));
    pixmap.lineTo(utils::from_string<float>(node->getAttribute("x2")),
                  utils::from_string<float>(node->getAttribute("y2")));

    pixmap.endPath();
}

void gdx_cpp::graphics::g2d::svg::SvgParser::parse_poly(gdx_cpp::utils::XmlReader::Element* node, bool close)
{
    pixmap.beginPath();

    parse_attr(node);
    
    std::string pointsStr = node->getAttribute("points");
    std::vector<float> points = splitArgs<float>(pointsStr, ", "); //it's line AND space

    for (unsigned int i = 0; i < points.size(); i += 2) {
        if (i % 2 == 0) {
            pixmap.lineTo(points[i], points[i+1]);
        } else {
            pixmap.moveTo(points[i], points[i+1]);
        }
    }

    if (close) {
        pixmap.closeSubPath();
    }

    pixmap.endPath();
}

void gdx_cpp::graphics::g2d::svg::SvgParser::parse_rect(gdx_cpp::utils::XmlReader::Element* node)
{
    pixmap.beginPath();
    parse_attr(node);

    float x = utils::from_string< float >(node->getAttribute("x")),
          y = utils::from_string< float >(node->getAttribute("y")),
          w = utils::from_string< float >(node->getAttribute("width")),
          h = utils::from_string< float >(node->getAttribute("height"));

    if(w != 0.0 && h != 0.0)
    {
        if(w < 0.0) {
            char buffer[1204];
            sprintf(buffer, "parse_rect: Invalid width: %f", w);
            throw std::runtime_error(buffer);
        }
        if(h < 0.0) {
            char buffer[1204];
            sprintf(buffer, "parse_rect: Invalid height: %f", h);
            throw std::runtime_error(buffer);
        }

        pixmap.moveTo(x,  y);
        pixmap.lineTo(x + w, y);
        pixmap.lineTo(x + w, y + h);
        pixmap.lineTo(x,     y + h);
        pixmap.closeSubPath();
    }

    pixmap.endPath();
}

void gdx_cpp::graphics::g2d::svg::SvgParser::parse_path(gdx_cpp::utils::XmlReader::Element* node)
{
    parse_attr(node);

    std::string path = node->getAttribute("d");

    std::vector<std::string> paths = splitArgs<std::string>(path, " ");

    unsigned int i = 0;

    while (i < paths.size()) {
        char cmd = paths[i][0];

        switch(cmd) {
            case 'M': case 'm':
                pixmap.moveTo(utils::from_string<float>(paths[i+1]), utils::from_string<float>(paths[i+2]), cmd == 'm');
                i += 3;
                break;
                
            case 'L': case 'l':
                pixmap.lineTo(utils::from_string<float>(paths[i+1]), utils::from_string<float>(paths[i+2]), cmd == 'l');
                i += 3;
                break;
                
            case 'V': case 'v':
                pixmap.verticalLineTo(utils::from_string<float>(paths[i+1]), cmd == 'v');
                i += 2;
                break;
                
            case 'H': case 'h':
                pixmap.horizontalLineTo(utils::from_string<float>(paths[i+1]), cmd == 'h');
                i += 2;
                break;
                
            case 'Q': case 'q':
                pixmap.curve3(utils::from_string<float>(paths[i+1]),
                              utils::from_string<float>(paths[i+2]),                                
                              utils::from_string<float>(paths[i+3]),
                              utils::from_string<float>(paths[i+4]),
                              cmd == 'q');
                i += 5;
                break;
                
            case 'T': case 't':
                pixmap.curve3(utils::from_string<float>(paths[i+1]), utils::from_string<float>(paths[i+2]), cmd == 't');
                i += 3;
                break;
                
            case 'C': case 'c':
                pixmap.curve4(utils::from_string<float>(paths[i+1]),
                              utils::from_string<float>(paths[i+2]),                              
                              utils::from_string<float>(paths[i+3]),
                              utils::from_string<float>(paths[i+4]),                              
                              utils::from_string<float>(paths[i+5]),
                              utils::from_string<float>(paths[i+6]),
                              cmd == 'c');
                i += 7;
                break;
                
            case 'S': case 's':
                pixmap.curve4(utils::from_string<float>(paths[i+1]),
                              utils::from_string<float>(paths[i+2]),
                              utils::from_string<float>(paths[i+3]),
                              utils::from_string<float>(paths[i+4]),
                              cmd == 's');
                i += 5;                
                break;
                
            case 'A': case 'a':
                throw std::runtime_error("parse_path: Command A: NOT IMPLEMENTED YET");
                
            case 'Z': case 'z':
                pixmap.closeSubPath();
                break;
                
            default:
            {
                char buf[100];
                sprintf(buf, "parse_path: Invalid Command %c", cmd);
                throw std::runtime_error(buf);
            }
        }
    }
    
}




