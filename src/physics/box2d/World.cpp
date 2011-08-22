
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

#include "World.hpp"

using namespace gdx_cpp::physics::box2d;

Body& World::newObject () {
    return new Body(World.this, 0);
}

Fixture& World::newObject () {
    return new Fixture(null, 0);
}

void World::rayCast (const RayCastCallback& callback,const gdx_cpp::math::Vector2& point1,const gdx_cpp::math::Vector2& point2) {
    rayCastCallback = callback;
    jniRayCast(addr, point1.x, point1.y, point2.x, point2.y);
}

float World::reportRayFixture (long addr,float pX,float pY,float nX,float nY,float fraction) {
    if (rayCastCallback != null)
        return rayCastCallback.reportRayFixture(fixtures.get(addr), rayPoint.set(pX, pY), rayNormal.set(nX, nY), fraction);
    else
        return 0.0f;
}

void World::setDestructionListener (const DestructionListener& listener) {

}

void World::setContactFilter (const ContactFilter& filter) {
    this.contactFilter = filter;
}

void World::setContactListener (const ContactListener& listener) {
    this.contactListener = listener;
}

Body& World::createBody (const BodyDef& def) {
    long bodyAddr = jniCreateBody(addr, def.type.getValue(), def.position.x, def.position.y, def.angle, def.linearVelocity.x,
                                  def.linearVelocity.y, def.angularVelocity, def.linearDamping, def.angularDamping, def.allowSleep, def.awake,
                                  def.fixedRotation, def.bullet, def.active, def.inertiaScale);
    Body body = freeBodies.obtain();
    body.reset(bodyAddr);
    this.bodies.put(body.addr, body);
    return body;
}

void World::destroyBody (const Body& body) {
    this.bodies.remove(body.addr);
    for (int i = 0; i < body.getFixtureList().size(); i++)
        this.fixtures.remove(body.getFixtureList().get(i).addr);
    for (int i = 0; i < body.getJointList().size(); i++)
        this.joints.remove(body.getJointList().get(i).joint.addr);
    jniDestroyBody(addr, body.addr);
    freeBodies.free(body);
}

Joint& World::createJoint (const JointDef& def) {
    long jointAddr = createProperJoint(def);
    Joint joint = null;
    if (def.type == JointType.DistanceJoint) joint = new DistanceJoint(this, jointAddr);
    if (def.type == JointType.FrictionJoint) joint = new FrictionJoint(this, jointAddr);
    if (def.type == JointType.GearJoint) joint = new GearJoint(this, jointAddr);
    if (def.type == JointType.LineJoint) joint = new LineJoint(this, jointAddr);
    if (def.type == JointType.MouseJoint) joint = new MouseJoint(this, jointAddr);
    if (def.type == JointType.PrismaticJoint) joint = new PrismaticJoint(this, jointAddr);
    if (def.type == JointType.PulleyJoint) joint = new PulleyJoint(this, jointAddr);
    if (def.type == JointType.RevoluteJoint) joint = new RevoluteJoint(this, jointAddr);
    if (def.type == JointType.WeldJoint) joint = new WeldJoint(this, jointAddr);
    if (joint != null) joints.put(joint.addr, joint);
    JointEdge jointEdgeA = new JointEdge(def.bodyB, joint);
    JointEdge jointEdgeB = new JointEdge(def.bodyA, joint);
    joint.jointEdgeA = jointEdgeA;
    joint.jointEdgeB = jointEdgeB;
    def.bodyA.joints.add(jointEdgeA);
    def.bodyB.joints.add(jointEdgeB);
    return joint;
}

long World::createProperJoint (const JointDef& def) {
    if (def.type == JointType.DistanceJoint) {
        DistanceJointDef d = (DistanceJointDef)def;
        return jniCreateDistanceJoint(addr, d.bodyA.addr, d.bodyB.addr, d.collideConnected, d.localAnchorA.x, d.localAnchorA.y,
                                      d.localAnchorB.x, d.localAnchorB.y, d.length, d.frequencyHz, d.dampingRatio);
    }
    if (def.type == JointType.FrictionJoint) {
        FrictionJointDef d = (FrictionJointDef)def;
        return jniCreateFrictionJoint(addr, d.bodyA.addr, d.bodyB.addr, d.collideConnected, d.localAnchorA.x, d.localAnchorA.y,
                                      d.localAnchorB.x, d.localAnchorB.y, d.maxForce, d.maxTorque);
    }
    if (def.type == JointType.GearJoint) {
        GearJointDef d = (GearJointDef)def;
        return jniCreateGearJoint(addr, d.bodyA.addr, d.bodyB.addr, d.collideConnected, d.joint1.addr, d.joint2.addr, d.ratio);
    }
    if (def.type == JointType.LineJoint) {
        LineJointDef d = (LineJointDef)def;
        return jniCreateLineJoint(addr, d.bodyA.addr, d.bodyB.addr, d.collideConnected, d.localAnchorA.x, d.localAnchorA.y,
                                  d.localAnchorB.x, d.localAnchorB.y, d.localAxisA.x, d.localAxisA.y, d.enableLimit, d.lowerTranslation,
                                  d.upperTranslation, d.enableMotor, d.maxMotorForce, d.motorSpeed);

    }
    if (def.type == JointType.MouseJoint) {
        MouseJointDef d = (MouseJointDef)def;
        return jniCreateMouseJoint(addr, d.bodyA.addr, d.bodyB.addr, d.collideConnected, d.target.x, d.target.y, d.maxForce,
                                   d.frequencyHz, d.dampingRatio);
    }
    if (def.type == JointType.PrismaticJoint) {
        PrismaticJointDef d = (PrismaticJointDef)def;
        return jniCreatePrismaticJoint(addr, d.bodyA.addr, d.bodyB.addr, d.collideConnected, d.localAnchorA.x, d.localAnchorA.y,
                                       d.localAnchorB.x, d.localAnchorB.y, d.localAxis1.x, d.localAxis1.y, d.referenceAngle, d.enableLimit,
                                       d.lowerTranslation, d.upperTranslation, d.enableMotor, d.maxMotorForce, d.motorSpeed);
    }
    if (def.type == JointType.PulleyJoint) {
        PulleyJointDef d = (PulleyJointDef)def;
        return jniCreatePulleyJoint(addr, d.bodyA.addr, d.bodyB.addr, d.collideConnected, d.groundAnchorA.x, d.groundAnchorA.y,
                                    d.groundAnchorB.x, d.groundAnchorB.y, d.localAnchorA.x, d.localAnchorA.y, d.localAnchorB.x, d.localAnchorB.y,
                                    d.lengthA, d.maxLengthA, d.lengthB, d.maxLengthB, d.ratio);

    }
    if (def.type == JointType.RevoluteJoint) {
        RevoluteJointDef d = (RevoluteJointDef)def;
        return jniCreateRevoluteJoint(addr, d.bodyA.addr, d.bodyB.addr, d.collideConnected, d.localAnchorA.x, d.localAnchorA.y,
                                      d.localAnchorB.x, d.localAnchorB.y, d.referenceAngle, d.enableLimit, d.lowerAngle, d.upperAngle, d.enableMotor,
                                      d.motorSpeed, d.maxMotorTorque);
    }
    if (def.type == JointType.WeldJoint) {
        WeldJointDef d = (WeldJointDef)def;
        return jniCreateWeldJoint(addr, d.bodyA.addr, d.bodyB.addr, d.collideConnected, d.localAnchorA.x, d.localAnchorA.y,
                                  d.localAnchorB.x, d.localAnchorB.y, d.referenceAngle);
    }

    return 0;
}

void World::destroyJoint (const Joint& joint) {
    joints.remove(joint.addr);
    joint.jointEdgeA.other.joints.remove(joint.jointEdgeB);
    joint.jointEdgeB.other.joints.remove(joint.jointEdgeA);
    jniDestroyJoint(addr, joint.addr);
}

void World::step (float timeStep,int velocityIterations,int positionIterations) {
    jniStep(addr, timeStep, velocityIterations, positionIterations);
}

void World::clearForces () {
    jniClearForces(addr);
}

void World::setWarmStarting (bool flag) {
    jniSetWarmStarting(addr, flag);
}

void World::setContinuousPhysics (bool flag) {
    jniSetContiousPhysics(addr, flag);
}

int World::getProxyCount () {
    return jniGetProxyCount(addr);
}

int World::getBodyCount () {
    return jniGetBodyCount(addr);
}

int World::getJointCount () {
    return jniGetJointcount(addr);
}

int World::getContactCount () {
    return jniGetContactCount(addr);
}

void World::setGravity (const gdx_cpp::math::Vector2& gravity) {
    jniSetGravity(addr, gravity.x, gravity.y);
}

gdx_cpp::math::Vector2& World::getGravity () {
    jniGetGravity(addr, tmpGravity);
    gravity.x = tmpGravity[0];
    gravity.y = tmpGravity[1];
    return gravity;
}

bool World::isLocked () {
    return jniIsLocked(addr);
}

void World::setAutoClearForces (bool flag) {
    jniSetAutoClearForces(addr, flag);
}

bool World::getAutoClearForces () {
    return jniGetAutoClearForces(addr);
}

void World::QueryAABB (const QueryCallback& callback,float lowerX,float lowerY,float upperX,float upperY) {
    queryCallback = callback;
    jniQueryAABB(addr, lowerX, lowerY, upperX, upperY);
}

std::list<Contact>& World::getContactList () {
    int numContacts = getContactCount();
    if (numContacts > contactAddrs.length) {
        int newSize = 2 * numContacts;
        contactAddrs = new long[newSize];
        contacts.ensureCapacity(newSize);
        freeContacts.ensureCapacity(newSize);
    }
    if (numContacts > freeContacts.size()) {
        int freeConts = freeContacts.size();
        for (int i = 0; i < numContacts - freeConts; i++)
            freeContacts.add(new Contact(this, 0));
    }
    jniGetContactList(addr, contactAddrs);

    contacts.clear();
    for (int i = 0; i < numContacts; i++) {
        Contact contact = freeContacts.get(i);
        contact.addr = contactAddrs[i];
        contacts.add(contact);
    }

    return contacts;
}

Iterator<Body>& World::getBodies () {
    return bodies.values();
}

Iterator<Joint>& World::getJoints () {
    return joints.values();
}

void World::dispose () {
    jniDispose(addr);
}

bool World::contactFilter (long fixtureA,long fixtureB) {
    if (contactFilter != null)
        return contactFilter.shouldCollide(fixtures.get(fixtureA), fixtures.get(fixtureB));
    else {
        Filter filterA = fixtures.get(fixtureA).getFilterData();
        Filter filterB = fixtures.get(fixtureB).getFilterData();

        if (filterA.groupIndex == filterB.groupIndex && filterA.groupIndex != 0) {
            return filterA.groupIndex > 0;
        }

        boolean collide = (filterA.maskBits & filterB.categoryBits) != 0 && (filterA.categoryBits & filterB.maskBits) != 0;
        return collide;
    }
}

void World::beginContact (long contactAddr) {
    contact.addr = contactAddr;
    if (contactListener != null) contactListener.beginContact(contact);
}

void World::endContact (long contactAddr) {
    contact.addr = contactAddr;
    if (contactListener != null) contactListener.endContact(contact);
}

void World::preSolve (long contactAddr,long manifoldAddr) {
    contact.addr = contactAddr;
    manifold.addr = manifoldAddr;
    if (contactListener != null) contactListener.preSolve(contact, manifold);
}

void World::postSolve (long contactAddr,long impulseAddr) {
    contact.addr = contactAddr;
    impulse.addr = impulseAddr;
    if (contactListener != null) contactListener.postSolve(contact, impulse);
}

bool World::reportFixture (long addr) {
    if (queryCallback != null)
        return queryCallback.reportFixture(fixtures.get(addr));
    else
        return false;
}

