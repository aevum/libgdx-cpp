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

#ifndef GDX_CPP_GRAPHICS_G2D_SVG_SVGPARSER_HPP
#define GDX_CPP_GRAPHICS_G2D_SVG_SVGPARSER_HPP

#include <stddef.h>
#include <string>
#include <utility>
#include <vector>

#include "gdx-cpp/graphics/Color.hpp"
#include "gdx-cpp/utils/SvgRendererHandler.hpp"
#include "gdx-cpp/utils/XmlReader.hpp"

namespace gdx {


class SvgPixmapInterface;

/** Uses the gdx-cpp built-in xml reader to parse svg files
 *
 * The parse is an rewrite of AGG built-in parser, which use SAX + expat. This way we have
 * an XML-engine independent parser.
 * 
 * @author Victor Vicente de Carvalho
 */
class SvgParser
{
public:   
    SvgParser();
    /**
    * iterate's over an svg xml element and fills the pixmap interface
    * @param iface The pixmap interface to be rendered
    * @param svg The parsed svg element pointer
    */
    static void render(XmlReader::Element* const svg, SvgRendererHandler* handler = nullptr);
private:
    ///Initiate the current element parsing
    static bool beginElement(gdx::XmlReader::Element*const currentNode);

    ///End's the current element parsing    
    static void endElement(XmlReader::Element* currentNode);

    static void parse_line(XmlReader::Element* node);
    static void parse_poly(gdx::XmlReader::Element* node, bool close);
    static void parse_rect(XmlReader::Element* node);
    static void parse_path(XmlReader::Element* node);
    static void parse_path_data(const char* data, int length);
    static void parse_attr(XmlReader::Element* node);
    static bool parse_attr(const std::string& name, const std::string& value);
    static void parse_transform(const std::string& transform_string, gdx::SvgRendererHandler::transform& transform);
    static std::vector< std::pair< std::string , std::string > > parse_style(const std::string& style);
    static std::string::size_type parse_scale(std::string scaleArgs, SvgRendererHandler::transform& transform);
    static std::string::size_type parse_translate(std::string translateArgs, SvgRendererHandler::transform& transform);
    static std::string::size_type parse_matrix(std::string matrixArgs, SvgRendererHandler::transform& result);
    static std::string::size_type parse_rotate(std::string rotateArgs, SvgRendererHandler::transform& transform);
    static std::string::size_type parse_skew_x(std::string skewXargs, SvgRendererHandler::transform& transform);
    static std::string::size_type parse_skew_y(std::string skewYargs, SvgRendererHandler::transform& transform);
    static Color parse_color(const std::string& colorValue);
    static void parse_gradient(const std::string& gradient);
    static void fetchStopData(gdx::XmlReader::Element* node , std::vector< gdx::SvgRendererHandler::GradientStopData >& stopData);
    static void fetchStopElement(gdx::XmlReader::Element* node, gdx::SvgRendererHandler::GradientStopData& stop );
    
    static bool m_titleFlag;
    static bool m_pathFlag;

    static SvgRendererHandler* handler;
    static XmlReader::Element* defsElement;
};

}

#endif // GDX_CPP_GRAPHICS_G2D_SVG_SVGPARSER_HPP
