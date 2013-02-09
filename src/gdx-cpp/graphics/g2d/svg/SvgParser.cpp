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

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cassert>
#include <memory>
#include <unordered_map>

#include "SvgParser.hpp"
#include "SvgPixmapInterface.hpp"
#include "gdx-cpp/Log.hpp"
#include "gdx-cpp/math/MathUtils.hpp"
#include "gdx-cpp/utils/StringConvertion.hpp"

using namespace gdx;

///splits the items inside argument calls like transform(129.2, 44)
template <typename T>
std::vector<T> splitArgs(const std::string& item, const char* delimiters, std::string::size_type& resultPos) {
    // Skip delimiters at beginning.
    std::string::size_type lastPos = item.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    std::string::size_type pos     = item.find_first_of(delimiters, lastPos);
    std::vector<T> result;

    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        result.push_back(gdx::from_string<T>(item.substr(lastPos, pos - lastPos)));
        // Skip delimiters.  Note the "not_of"
        lastPos = item.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = item.find_first_of(delimiters, lastPos);
    }

    resultPos = lastPos;

    return result;
}

gdx::SvgRendererHandler* SvgParser::handler = NULL;
bool SvgParser::m_titleFlag = false;
bool SvgParser::m_pathFlag = false;
gdx::XmlReader::Element* SvgParser::defsElement = NULL;

void SvgParser::render(gdx::XmlReader::Element*const svg, gdx::SvgRendererHandler* p_handler)
{
    m_pathFlag = false;
    m_titleFlag = false;

    if (p_handler) {
        handler = p_handler;
        defsElement = NULL;
    }

    assert(handler != NULL);

    if (beginElement(svg)) {

        for (int i = 0; i < svg->getChildCount(); ++i) {
            SvgParser::render(svg->getChild(i).get());
        }
    }

    endElement(svg);
}

bool SvgParser::beginElement(XmlReader::Element*const currentNode)
{
    std::string name = currentNode->getName();

    if (name == "svg" || name == "svg:svg") {
        int width = from_string<float>(currentNode->getAttribute("width"));
        int height = from_string<float>(currentNode->getAttribute("height"));

        handler->setImageDimension(width, height);
    }
    if (name == "title" || name == "svg:title")
    {
        m_titleFlag = true;
    }
    else if (name == "g" || name == "svg:g")
    {
        handler->begin();
        parse_attr(currentNode);
    }
    else if (name == "path" || name == "svg:path")
    {
        if (m_pathFlag)
        {
            gdx_log_error("gdx","start_element: Nested path");
        }

        handler->beginPath();
        parse_path(currentNode);
        handler->endPath();
        m_pathFlag = true;
    }
    else if (name == "rect" || name == "svg:rect")
    {
        parse_rect(currentNode);
    }
    else if (name == "line" || name == "svg:line")
    {
        parse_line(currentNode);
    }
    else if (name == "polyline" || name == "svg:polyline")
    {
        parse_poly(currentNode, false);
    }
    else if (name == "polygon" ||  name == "svg:polygon")
    {
        parse_poly(currentNode, true);
    } else if (name == "defs" || name == "svg:defs") {
        defsElement = currentNode;
    } else if (name == "clipPath" || name == "svg:clipPath") {
        return false;
    }

    return true;
}

void SvgParser::endElement(XmlReader::Element* currentNode)
{
    std::string name = currentNode->getName();

    if (name == "title" || name == "svg:title")
    {
        m_titleFlag = false;
    }
    else if (name == "g" || name == "svg:g")
    {
        handler->end();
    }
    else if (name == "path" || name == "svg:path")
    {
        m_pathFlag = false;
    }
}

void gdx::SvgParser::parse_attr(gdx::XmlReader::Element* node)
{
    XmlReader::Element::AttributesMap::const_iterator it = node->getAttributesBegin();
    XmlReader::Element::AttributesMap::const_iterator end = node->getAttributesEnd();

    for (; it != end; ++it) {
        if (it->first == "style") {
            std::vector< std::pair< std::string , std::string > > res = parse_style(it->second);
            for (unsigned int i = 0; i < res.size(); ++i) {
                parse_attr(res[i].first, res[i].second);
            }
        } else {
            parse_attr(it->first, it->second);
        }
    }
}

std::vector< std::pair< std::string , std::string > > gdx::SvgParser::parse_style(const std::string& style)
{
    std::string::size_type result = 0;
    std::vector<std::string> res =  splitArgs<std::string>(style, ":;", result);
    std::vector< std::pair< std::string , std::string > > ret;

    for (int i = 0; i < res.size(); i += 2) {
        std::remove(res[i].begin(), res[i].end(), ' ');
        std::remove(res[i+1].begin(), res[i+1].end(), ' ');
        ret.push_back( std::make_pair(res[i], res[i+1]) );
    }

    return ret;
}

bool gdx::SvgParser::parse_attr(const std::string& name, const std::string& value)
{
    if (name == "style")
    {
        std::vector< std::pair< std::string , std::string > > res = parse_style(value);
        for (int i = 0; i < res.size(); ++i) {
            parse_attr(res[i].first, res[i].second);
        }
    }
    else if (name == "fill")
    {
        if (value == "none")
        {
            handler->fillNone();
        }
        else
        {
            if (value.find("url") != std::string::npos) {
                parse_gradient(value);
            } else {
                handler->fill(parse_color(value));
            }
        }
    }
    else if (name == "fill-opacity" || name == "opacity")
    {
        handler->fillOpacity(from_string<double>(value));
    }
    else  if (name == "stroke")
    {
        if (value == "none")
        {
            handler->strokeNone();
        }
        else
        {
            handler->stroke(parse_color(value));
        }
    }
    else if (name == "stroke-width")
    {
        handler->setStrokeWidth(from_string<float>(value));
    }
    else if (name == "stroke-linecap")
    {
        if (value == "butt")        handler->setLineCap(SvgPixmapInterface::ButtLineCap);
        else if (value == "round")  handler->setLineCap(SvgPixmapInterface::RoundLineCap);
        else if (value == "square") handler->setLineCap(SvgPixmapInterface::SquareLineCap);
    }
    else if (name == "stroke-linejoin")
    {
        if (value == "miter")      handler->setLineJoin(SvgPixmapInterface::MiterJoin);
        else if (value == "round") handler->setLineJoin(SvgPixmapInterface::RoundJoin);
        else if (value == "bevel") handler->setLineJoin(SvgPixmapInterface::BevelJoin);
    }
    else if (name == "stroke-miterlimit")
    {
        handler->setMiterLimit(from_string<double>(value));
    }
    else if (name == "stroke-opacity")
    {
        handler->setStrokeOpacity(from_string<double>(value));
    }
    else if (name == "transform")
    {
        parse_transform(value, handler->currentTransform());
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

void gdx::SvgParser::parse_transform(const std::string& transform_string,
        SvgRendererHandler::transform& transform)
{
    std::string::size_type pos = 0, last = 0;

    struct delegates {
        const char* name;
        std::string::size_type (*func)(std::string, SvgRendererHandler::transform& applier );
    };

    static delegates transform_parsers[] = {
        { "matrix", &SvgParser::parse_matrix },
        { "translate", &SvgParser::parse_translate },
        { "rotate", &SvgParser::parse_rotate },
        { "scale", &SvgParser::parse_scale },
        { "skewX", &SvgParser::parse_skew_x },
        { "skewY", &SvgParser::parse_skew_y },
    };

    while (pos != std::string::npos && last != std::string::npos) {
        for (int i = 0; i < 6; ++i) {
            pos = transform_string.find(transform_parsers[i].name, last);
            if (pos != std::string::npos) {
                pos += strlen(transform_parsers[i].name);
                last = (*transform_parsers[i].func)(transform_string.substr(pos, transform_string.length() - last - 1), transform);
                break;
            }
        }
    }
}


std::string::size_type gdx::SvgParser::parse_matrix(std::string matrixArgs,
        gdx::SvgRendererHandler::transform& transform)
{
    std::string::size_type result = 0;
    std::vector<float> res = splitArgs<float>(matrixArgs, "(, )", result);

    assert(res.size() == 6);

    transform.affine(res);

    return result;
}

std::string::size_type gdx::SvgParser::parse_rotate(std::string rotateArgs, SvgRendererHandler::transform& transform)
{
    std::string::size_type result = 0;
    std::vector<float> res = splitArgs<float>(rotateArgs, "(, )", result);

    if (res.size() == 1) {
        transform.rotate(toRadians(res[0]));
    } else if (res.size() == 3) {
        transform.rotate_trasnlate(toRadians(res[0]), res[1], res[2]);
    } else {
        gdx_log_error("gdx","SvgParser::parse_rotate: invalid number of arguments");
    }

    return result;
}

std::string::size_type gdx::SvgParser::parse_scale(std::string scaleArgs,
        SvgRendererHandler::transform& transform)
{
    std::string::size_type result = 0;
    std::vector<float> res = splitArgs<float>(scaleArgs, "(, )", result);

    assert(res.size() >= 1);

    if (res.size() == 1) {
        res.push_back(res[0]);
    }

    transform.scale(res[0], res[1]);

    return result;
}

std::string::size_type gdx::SvgParser::parse_skew_x(std::string skewXargs,
        SvgRendererHandler::transform& transform)
{
    std::string::size_type result = 0;
    std::vector<float> res = splitArgs<float>(skewXargs, "(, )", result);

    assert(res.size() == 1);

    transform.skew_x(res[0]);

    return result;
}

std::string::size_type gdx::SvgParser::parse_skew_y(std::string skewYargs, SvgRendererHandler::transform& transform)
{
    std::string::size_type result = 0;
    std::vector<float> res = splitArgs<float>(skewYargs, "(, )", result);

    assert(res.size() == 1);

    transform.skew_y(res[0]);

    return result;
}

std::string::size_type gdx::SvgParser::parse_translate(std::string translateArgs, SvgRendererHandler::transform& transform)
{
    std::string::size_type result = 0;
    std::vector<float> res = splitArgs<float>(translateArgs, "(, )", result);

    assert(res.size() >= 1);
    if (res.size() == 1) res.push_back(0);

    transform.translate(res[0], res[1]);
    return result;
}

gdx::Color gdx::SvgParser::parse_color(const std::string& colorValue)
{
    std::string::size_type pos = colorValue.find("#") + 1;

    if (pos != std::string::npos) {
        int color;
        if (colorValue.size() == 4) {
            char color_buf[7] = { 0 };
            color_buf[0] = color_buf[1] = colorValue[1];
            color_buf[2] = color_buf[3] = colorValue[2];
            color_buf[4] = color_buf[5] = colorValue[3];
            sscanf(color_buf, "%x", &color);
        } else {

            sscanf(&colorValue[pos], "%x", &color);
        }

        return Color::fromRgb(color);
    } else if ((pos = colorValue.find("rgb")) != std::string::npos) {
        gdx_log_error("gdx","No implemented yet");
    } else {
        gdx_log_error("gdx","No implemented yet");
    }
}

void gdx::SvgParser::parse_line(gdx::XmlReader::Element* node)
{
    handler->beginPath();

    parse_attr(node);

    handler->moveTo(from_string<float>(node->getAttribute("x1")),
                    from_string<float>(node->getAttribute("y1")));
    handler->lineTo(from_string<float>(node->getAttribute("x2")),
                    from_string<float>(node->getAttribute("y2")));

    handler->endPath();
}

void gdx::SvgParser::parse_poly(gdx::XmlReader::Element* node, bool close)
{
    handler->beginPath();

    parse_attr(node);

    std::string pointsStr = node->getAttribute("points");
    std::string::size_type result = 0;
    std::vector<float> points = splitArgs<float>(pointsStr, ", ", result); //it's line AND space

    for (unsigned int i = 0; i < points.size(); i += 2) {
        if (i % 2 == 0) {
            handler->lineTo(points[i], points[i+1]);
        } else {
            handler->moveTo(points[i], points[i+1]);
        }
    }

    if (close) {
        handler->closeSubPath();
    }

    handler->endPath();
}

void gdx::SvgParser::parse_rect(gdx::XmlReader::Element* node)
{
    handler->beginPath();
    parse_attr(node);

    float x = from_string< float >(node->getAttribute("x")),
          y = from_string< float >(node->getAttribute("y")),
          w = from_string< float >(node->getAttribute("width")),
          h = from_string< float >(node->getAttribute("height"));

    if(w != 0.0 && h != 0.0)
    {
        if(w < 0.0) {
            char buffer[1204];
            sprintf(buffer, "parse_rect: Invalid width: %f", w);
            gdx_log_error("gdx",buffer);
        }
        if(h < 0.0) {
            char buffer[1204];
            sprintf(buffer, "parse_rect: Invalid height: %f", h);
            gdx_log_error("gdx",buffer);
        }

        handler->moveTo(x,  y);
        handler->lineTo(x + w, y);
        handler->lineTo(x + w, y + h);
        handler->lineTo(x,     y + h);
        handler->closeSubPath();
    }

    handler->endPath();
}

void gdx::SvgParser::parse_path(gdx::XmlReader::Element* node)
{
    parse_attr(node);

    std::string path = node->getAttribute("d");

//     std::string::size_type result = 0;
//         std::vector<std::string> paths = splitArgs<std::string>(path, " ,", result);
//         static const char commands[]   = "MmZzLlHhVvCcSsQqTtAaFfPp";
//
//         unsigned int i = 0;
//
//         char cmd = paths[0][0];
//
//         while (i < paths.size()) {
//                 int j = 0;
//                 for (;j < strlen(commands) && commands[j] != paths[i][0]; ++j)
//                     ;
//
//                 if (j < strlen(commands)) {
//                         cmd = paths[i++][0];
//                     }
//
//                     switch(cmd) {
//                             case 'M': case 'm':
//                                 handler->moveTo(from_string<float>(paths[i]), from_string<float>(paths[i+1]), cmd == 'm');
//                                 cmd = cmd == 'm' ? 'l' : 'L';
//                                 i += 2;
//                                 break;
//
//                             case 'L': case 'l':
//                                 handler->lineTo(from_string<float>(paths[i]), from_string<float>(paths[i+1]), cmd == 'l');
//                                 i += 2;
//                                 break;
//
//                             case 'V': case 'v':
//                                 handler->verticalLineTo(from_string<float>(paths[i]), cmd == 'v');
//                                 i += 1;
//                                 break;
//
//                             case 'H': case 'h':
//                                 handler->horizontalLineTo(from_string<float>(paths[i]), cmd == 'h');
//                                 i += 1;
//                                 break;
//
//                             case 'Q': case 'q':
//                                 handler->curve3(from_string<float>(paths[i]),
//                                                                                from_string<float>(paths[i+1]),
//                                                                                from_string<float>(paths[i+2]),
//                                                                                from_string<float>(paths[i+3]),
//                                                                                cmd == 'q');
//                                 i += 4;
//                                 break;
//
//                             case 'T': case 't':
//                                 handler->curve3(from_string<float>(paths[i]), from_string<float>(paths[i+1]), cmd == 't');
//                                 i += 2;
//                                 break;
//
//                             case 'C': case 'c':
//                                 handler->curve4(from_string<float>(paths[i]),
//                                                                                from_string<float>(paths[i+1]),
//                                                                                from_string<float>(paths[i+2]),
//                                                                                from_string<float>(paths[i+3]),
//                                                                                from_string<float>(paths[i+4]),
//                                                                                from_string<float>(paths[i+5]),
//                                                                                cmd == 'c');
//                                 i += 6;
//                                 break;
//
//                             case 'S': case 's':
//                                 handler->curve4(from_string<float>(paths[i]),
//                                                                                from_string<float>(paths[i+1]),
//                                                                                from_string<float>(paths[i+2]),
//                                                                                from_string<float>(paths[i+3]),
//                                                                                cmd == 's');
//                                 i += 4;
//                                 break;
//
//                             case 'A': case 'a':
//                                 gdx_log_error("gdx","parse_path: Command A: NOT IMPLEMENTED YET");
//
//                             case 'Z': case 'z':
//                                 handler->closeSubPath();
//                                 break;
//
//                             default:
//                             {
//                                     char buf[100];
//                                     sprintf(buf, "parse_path: Invalid Command %c", cmd);
//                                     gdx_log_error("gdx",buf);
//                                 }
//                             }
//                         }


    parse_path_data(path.c_str(), path.size());
}

void gdx::SvgParser::fetchStopData(gdx::XmlReader::Element* node , std::vector< SvgRendererHandler::GradientStopData >& stopData) {
    for( int i = 0; i < node->getChildCount(); ++i) {
        gdx::XmlReader::Element::ptr child = node->getChild(i);
        if (child->getName() == "svg:stop" || child->getName() == "stop") {
            SvgRendererHandler::GradientStopData stop;
            stop.offset = from_string< float >(child->getAttribute("offset"));

            if (child->hasAttribute("style")) {
                std::vector< std::pair< std::string , std::string > > res = parse_style(child->getAttribute("style"));

                for (int i = 0; i < res.size(); ++i) {
                    if (res[i].first == "stop-color") {
                        stop.color = parse_color(res[i].second);
                    } else if (res[i].first == "stop-opacity") {
                        stop.opacity = from_string< float >(res[i].second);
                    }
                }
            }

            if (child->hasAttribute("stop-color")) {
                stop.color = parse_color(child->getAttribute("stop-color"));
            }

            if (child->hasAttribute("stop-opacity")) {
                stop.opacity = from_string< float >(child->getAttribute("stop-opacity"));
            }

            stopData.push_back(stop);
        }
    }

    if (node->hasAttribute("xlink:href")) {
        std::string nodeName =  node->getAttribute("xlink:href").substr(1);

        for (int i = 0; i < defsElement->getChildCount(); ++i) {
            if (defsElement->getChild(i)->getAttribute("id") == nodeName) {
                fetchStopData(defsElement->getChild(i).get(), stopData);
                break;
            }
        }
    }
}

bool sortByStop(const SvgRendererHandler::GradientStopData& a,const SvgRendererHandler::GradientStopData& b) {
    return a.offset < b.offset;
}

void gdx::SvgParser::parse_gradient(const std::string& gradient)
{
    std::string::size_type result = 0;
    std::vector< std::string > url = splitArgs<std::string>(gradient, "()", result);
    
    float x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    handler->boundingRect(x1, y1, x2, y2);
    
    assert(defsElement != NULL);

    std::string gradientNodeUrl = url[1].substr(1);

    gdx::XmlReader::Element::ptr gradientDef;

    for (int i = 0; i < defsElement->getChildCount(); ++i) {
        if (defsElement->getChild(i)->getAttribute("id") == gradientNodeUrl) {
            gradientDef = defsElement->getChild(i);
            break;
        }
    }

    assert(gradientDef);
    
    if ( gradientDef->getName() == "svg:linearGradient" || gradientDef->getName() == "linearGradient") {
        SvgRendererHandler::LinearGradient gradientData;

        fetchStopData(gradientDef.get(), gradientData.stops);

        std::sort(gradientData.stops.begin(), gradientData.stops.end(), sortByStop);

        if (gradientDef->hasAttribute("x1")) {
            gradientData.x1 = from_string< float >(gradientDef->getAttribute("x1"));
        } else {
            gradientData.x1 = x1;
        }

        if (gradientDef->hasAttribute("y1")) {
            gradientData.y1 = from_string< float >(gradientDef->getAttribute("y1"));
        } else {
            gradientData.y1 = y1;
        }

        if (gradientDef->hasAttribute("x2")) {
            gradientData.x2 = from_string< float >(gradientDef->getAttribute("x2"));
        } else {
            gradientData.x2 = x2;
        }

        if (gradientDef->hasAttribute("y2")) {
            gradientData.y2 = from_string< float >(gradientDef->getAttribute("y2"));
        } else {
            gradientData.y2 = y2;
        }

        if (gradientDef->hasAttribute("gradientTransform")) {
            gradientData.gradient_transform = handler->createTransform();
            std::string gradientTransform = gradientDef->getAttribute("gradientTransform");
            parse_transform(gradientTransform, *gradientData.gradient_transform);
        }

        handler->fillLinearGradient(gradientData);
    } else if ( gradientDef->getName() == "svg:radialGradient" || gradientDef->getName() == "radialGradient") {
        SvgRendererHandler::RadialGradient gradientData;

        fetchStopData(gradientDef.get(), gradientData.stops);

        std::sort(gradientData.stops.begin(), gradientData.stops.end(), sortByStop);

        gradientData.cx = from_string< float >(gradientDef->getAttribute("cx"));
        gradientData.cy = from_string< float >(gradientDef->getAttribute("cy"));
        if (gradientDef->hasAttribute("fx")) {
            gradientData.fx = from_string< float >(gradientDef->getAttribute("fx"));
        } else {
            gradientData.fx = gradientData.cx;
        }
        if (gradientDef->hasAttribute("fy")) {
            gradientData.fy = from_string< float >(gradientDef->getAttribute("fy"));
        } else {
            gradientData.fy = gradientData.cy;
        }

        gradientData.r = from_string< float >(gradientDef->getAttribute("r"));

        if (gradientDef->hasAttribute("gradientTransform")) {
            gradientData.gradient_transform = handler->createTransform();
            std::string gradientTransform = gradientDef->getAttribute("gradientTransform");
            parse_transform(gradientTransform, *gradientData.gradient_transform);
        }

        handler->fillRadialGradient(gradientData);
    }
}

