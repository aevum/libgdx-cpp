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

#include "gdx-cpp/utils/XmlReader.hpp"
#include "SvgPixmapInterface.hpp"
#include "gdx-cpp/graphics/Color.hpp"

namespace gdx_cpp {

namespace graphics {

namespace g2d {

namespace svg {

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
    SvgParser(SvgPixmapInterface& iface);
    
    /**
    * iterate's over an svg xml element and fills the pixmap interface
    * @param iface The pixmap interface to be rendered
    * @param svg The parsed svg element pointer
    */
    void render(utils::XmlReader::Element* const svg);
private:

    ///Initiate the current element parsing
    void beginElement(gdx_cpp::utils::XmlReader::Element*const currentNode);

    ///End's the current element parsing    
    void endElement(utils::XmlReader::Element* currentNode);

    void parse_line(utils::XmlReader::Element* node);
    void parse_poly(gdx_cpp::utils::XmlReader::Element* node, bool close);
    void parse_rect(utils::XmlReader::Element* node);
    void parse_path(utils::XmlReader::Element* node);    
    void parse_attr(utils::XmlReader::Element* node);
    bool parse_attr(const std::string& name, const std::string& value);
    void parse_transform(const std::string& transform);
    void parse_style(const std::string& style);
    void parse_scale(std::string scaleArgs);
    void parse_translate(std::string translateArgs);
    void parse_matrix(std::string matrixArgs);
    void parse_rotate(std::string rotateArgs);
    void parse_skew_x(std::string skewXargs);
    void parse_skew_y(std::string skewYargs);
    graphics::Color parse_color(const std::string& colorValue);
    
    bool m_titleFlag;
    bool m_pathFlag;

    SvgPixmapInterface& pixmap;
};

}
}
}

}

#endif // GDX_CPP_GRAPHICS_G2D_SVG_SVGPARSER_HPP
