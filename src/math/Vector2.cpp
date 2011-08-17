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


#include <gdx/math/Vector2.hpp>

#include <math.h>

using namespace gdx_cpp::math;

Vector2::Vector2() : x(0.0), y(0.0)
{
}

Vector2::Vector2(float _x, float _y) : x(_x), y(_y)
{
}

Vector2::Vector2(const Vector2& other)
{
  set(other);
}

float Vector2::len () {
  return (float)stlport::sqrt(x * x + y * y);
}

Vector2::~Vector2()
{
}

Vector2& Vector2::operator=(const Vector2& other)
{
    return *this;
}

bool Vector2::operator==(const Vector2& other) const
{

}

Vector2& Vector2::set (Vector2 v) {
  x = v.x;
  y = v.y;
  return *this;
}

Vector2& Vector2::sub (Vector2 v) {
  x -= v.x;
  y -= v.y;
  return *this;
}

Vector2 Vector2::nor (){
  float len = len();
  if (len != 0) {
    x /= len;
    y /= len;
  }
  return this;
}


Vector2 Vector2::add (Vector2 v){
  x += v.x;
  y += v.y;
  return this;
}

Vector2 Vector2::add (float x, float y){
  this.x += x;
  this.y += y;
  return this;
}


float Vector2::dot (Vector2 v){
  return x * v.x + y * v.y;
}


Vector2 Vector2::mul (float scalar){
  x *= scalar;
  y *= scalar;
  return this;
}


float Vector2::dst (Vector2 v){
  final float x_d = v.x - x;
  final float y_d = v.y - y;
  return (float)Math.sqrt(x_d * x_d + y_d * y_d);
}

float Vector2::dst (float x, float y){
  final float x_d = x - this.x;
  final float y_d = y - this.y;
  return (float)Math.sqrt(x_d * x_d + y_d * y_d);
}

float Vector2::dst2 (Vector2 v){
  final float x_d = v.x - x;
  final float y_d = v.y - y;
  return x_d * x_d + y_d * y_d;
}

String Vector2::toString (){
  return "[" + x + ":" + y + "]";
}

Vector2 Vector2::sub (float x, float y){
  this.x -= x;
  this.y -= y;
  return this;
}

Vector2 Vector2::tmp (){
  return tmp.set(this);
}

Vector2 Vector2::mul (Matrix3 mat){
  float x = this.x * mat.vals[0] + this.y * mat.vals[3] + mat.vals[6];
  float y = this.x * mat.vals[1] + this.y * mat.vals[4] + mat.vals[7];
  this.x = x;
  this.y = y;
  return this;
}

float Vector2::crs (Vector2 v){
  return this.x * v.y - this.y * v.x;
}

float Vector2::crs (float x, float y){
  return this.x * y - this.y * x;
}

float Vector2::angle (){
  float angle = (float)Math.atan2(y, x) * MathUtils.radiansToDegrees;
  if (angle < 0) angle += 360;
  return angle;
}

Vector2 Vector2::rotate (float angle){
  float rad = angle * MathUtils.degreesToRadians;
  float cos = (float)Math.cos(rad);
  float sin = (float)Math.sin(rad);
  
  float newX = this.x * cos - this.y * sin;
  float newY = this.x * sin + this.y * cos;
  
  this.x = newX;
  this.y = newY;
  
  return this;
}

Vector2 Vector2::lerp (Vector2 target, float alpha){
  Vector2 r = this.mul(1.0f - alpha);
  r.add(target.tmp().mul(alpha));
  return r;
}


