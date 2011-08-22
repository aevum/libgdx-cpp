
/*
    Copyright 2011 Aevum Software aevum @ aevumlab.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
    @author Ozires Bortolon de Faria ozires@aevumlab.com
*/

#ifndef GDX_CPP_UTILS_XMLREADER_HPP_
#define GDX_CPP_UTILS_XMLREADER_HPP_

namespace gdx_cpp {
namespace utils {

class XmlReader {
public:
    Element& parse (const std::string& xml);
    Element& parse (const Reader& reader);
    Element& parse (const InputStream& input);
    Element& parse (const gdx_cpp::files::FileHandle& file);
    Element& parse (int offset,int length);
    std::string& getName ();
    std::string& getAttribute (const std::string& name);
    std::string& getAttribute (const std::string& name,const std::string& defaultValue);
    void setAttribute (const std::string& name,const std::string& value);
    int getChildCount ();
    Element& getChild (int i);
    void addChild (const Element& element);
    std::string& getText ();
    void setText (const std::string& text);
    std::string& toString ();
    std::string& toString (const std::string& indent);
    Element& getChildByName (const std::string& name);
    Element& getChildByNameRecursive (const std::string& name);
    Array<Element>& getChildrenByName (const std::string& name);
    float getFloatAttribute (const std::string& name);
    float getFloatAttribute (const std::string& name,float defaultValue);
    int getIntAttribute (const std::string& name);
    int getIntAttribute (const std::string& name,int defaultValue);
    bool getBooleanAttribute (const std::string& name);
    bool getBooleanAttribute (const std::string& name,bool defaultValue);
    std::string& get (const std::string& name);
    std::string& get (const std::string& name,const std::string& defaultValue);
    int getInt (const std::string& name);
    int getInt (const std::string& name,int defaultValue);
    float getFloat (const std::string& name);
    float getFloat (const std::string& name,float defaultValue);
    bool getBolean (const std::string& name);
    bool getBoolean (const std::string& name,bool defaultValue);

protected:
    void open (const std::string& name);
    void attribute (const std::string& name,const std::string& value);
    std::string& entity (const std::string& name);
    void text (const std::string& text);
    void close ();

private:
    static char* init__xml_actions_0 ();
    static char* init__xml_key_offsets_0 ();
    static char* init__xml_trans_keys_0 ();
    static char* init__xml_single_lengths_0 ();
    static char* init__xml_range_lengths_0 ();
    static short* init__xml_index_offsets_0 ();
    static char* init__xml_indicies_0 ();
    static char* init__xml_trans_targs_0 ();
    static char* init__xml_trans_actions_0 ();
    String name;
};

} // namespace gdx_cpp
} // namespace utils

#endif // GDX_CPP_UTILS_XMLREADER_HPP_
