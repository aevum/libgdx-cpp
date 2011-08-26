/*
    Copyright 2011 <copyright holder> <email>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/


#ifndef GENERICBUFFER _HPP
#define GENERICBUFFER _HPP

class GenericBuffer <T>
{

public:
    GenericBuffer();
    GenericBuffer(const GenericBuffer& other);
    virtual ~GenericBuffer();
    virtual GenericBuffer& operator=(const GenericBuffer& other);
    virtual bool operator==(const GenericBuffer& other) const;

protected:

private:
  T* buffer[];
  int mark = -1;
  int position = 0;
  int limit;
  int capacity;
};

#endif // GENERICBUFFER _HPP
