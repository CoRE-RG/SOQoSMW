//
// Generated file, do not edit! Created by nedtool 5.1 from soqosmw/qosmanagement/negotiation/messages/QoSNegotiationMessages.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "QoSNegotiationMessages_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace soqosmw {

// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("soqosmw::QoSGroups");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("soqosmw::QoSGroups"));
    e->insert(QoSGroup_RT, "QoSGroup_RT");
    e->insert(QoSGroup_STD, "QoSGroup_STD");
    e->insert(QoSGroup_WEB, "QoSGroup_WEB");
)

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("soqosmw::QoSNegotiationMsgType");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("soqosmw::QoSNegotiationMsgType"));
    e->insert(QoS_Request, "QoS_Request");
    e->insert(QoS_Response, "QoS_Response");
)

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("soqosmw::QoSConnectionEstablishMsgType");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("soqosmw::QoSConnectionEstablishMsgType"));
    e->insert(Establish_Request, "Establish_Request");
    e->insert(Establish_Success, "Establish_Success");
    e->insert(Establish_Failure, "Establish_Failure");
)

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("soqosmw::QoSNegotiationResponseStatus");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("soqosmw::QoSNegotiationResponseStatus"));
    e->insert(QoS_ResponseStatusSuccess, "QoS_ResponseStatusSuccess");
    e->insert(QoS_ResponseStatusFailure, "QoS_ResponseStatusFailure");
)

Register_Class(QoSNegotiationPayload)

QoSNegotiationPayload::QoSNegotiationPayload(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->qosGroup = 0;
}

QoSNegotiationPayload::QoSNegotiationPayload(const QoSNegotiationPayload& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

QoSNegotiationPayload::~QoSNegotiationPayload()
{
}

QoSNegotiationPayload& QoSNegotiationPayload::operator=(const QoSNegotiationPayload& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void QoSNegotiationPayload::copy(const QoSNegotiationPayload& other)
{
    this->qosGroup = other.qosGroup;
}

void QoSNegotiationPayload::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->qosGroup);
}

void QoSNegotiationPayload::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->qosGroup);
}

int QoSNegotiationPayload::getQosGroup() const
{
    return this->qosGroup;
}

void QoSNegotiationPayload::setQosGroup(int qosGroup)
{
    this->qosGroup = qosGroup;
}

class QoSNegotiationPayloadDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    QoSNegotiationPayloadDescriptor();
    virtual ~QoSNegotiationPayloadDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(QoSNegotiationPayloadDescriptor)

QoSNegotiationPayloadDescriptor::QoSNegotiationPayloadDescriptor() : omnetpp::cClassDescriptor("soqosmw::QoSNegotiationPayload", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

QoSNegotiationPayloadDescriptor::~QoSNegotiationPayloadDescriptor()
{
    delete[] propertynames;
}

bool QoSNegotiationPayloadDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<QoSNegotiationPayload *>(obj)!=nullptr;
}

const char **QoSNegotiationPayloadDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *QoSNegotiationPayloadDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int QoSNegotiationPayloadDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int QoSNegotiationPayloadDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *QoSNegotiationPayloadDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "qosGroup",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int QoSNegotiationPayloadDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='q' && strcmp(fieldName, "qosGroup")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *QoSNegotiationPayloadDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **QoSNegotiationPayloadDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *QoSNegotiationPayloadDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "soqosmw::QoSGroups";
            return nullptr;
        default: return nullptr;
    }
}

int QoSNegotiationPayloadDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationPayload *pp = (QoSNegotiationPayload *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *QoSNegotiationPayloadDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationPayload *pp = (QoSNegotiationPayload *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string QoSNegotiationPayloadDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationPayload *pp = (QoSNegotiationPayload *)object; (void)pp;
    switch (field) {
        case 0: return enum2string(pp->getQosGroup(), "soqosmw::QoSGroups");
        default: return "";
    }
}

bool QoSNegotiationPayloadDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationPayload *pp = (QoSNegotiationPayload *)object; (void)pp;
    switch (field) {
        case 0: pp->setQosGroup((soqosmw::QoSGroups)string2enum(value, "soqosmw::QoSGroups")); return true;
        default: return false;
    }
}

const char *QoSNegotiationPayloadDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *QoSNegotiationPayloadDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationPayload *pp = (QoSNegotiationPayload *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(QoSNegotiationRequestPayload)

QoSNegotiationRequestPayload::QoSNegotiationRequestPayload(const char *name, short kind) : ::soqosmw::QoSNegotiationPayload(name,kind)
{
}

QoSNegotiationRequestPayload::QoSNegotiationRequestPayload(const QoSNegotiationRequestPayload& other) : ::soqosmw::QoSNegotiationPayload(other)
{
    copy(other);
}

QoSNegotiationRequestPayload::~QoSNegotiationRequestPayload()
{
}

QoSNegotiationRequestPayload& QoSNegotiationRequestPayload::operator=(const QoSNegotiationRequestPayload& other)
{
    if (this==&other) return *this;
    ::soqosmw::QoSNegotiationPayload::operator=(other);
    copy(other);
    return *this;
}

void QoSNegotiationRequestPayload::copy(const QoSNegotiationRequestPayload& other)
{
}

void QoSNegotiationRequestPayload::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::soqosmw::QoSNegotiationPayload::parsimPack(b);
}

void QoSNegotiationRequestPayload::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::soqosmw::QoSNegotiationPayload::parsimUnpack(b);
}

class QoSNegotiationRequestPayloadDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    QoSNegotiationRequestPayloadDescriptor();
    virtual ~QoSNegotiationRequestPayloadDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(QoSNegotiationRequestPayloadDescriptor)

QoSNegotiationRequestPayloadDescriptor::QoSNegotiationRequestPayloadDescriptor() : omnetpp::cClassDescriptor("soqosmw::QoSNegotiationRequestPayload", "soqosmw::QoSNegotiationPayload")
{
    propertynames = nullptr;
}

QoSNegotiationRequestPayloadDescriptor::~QoSNegotiationRequestPayloadDescriptor()
{
    delete[] propertynames;
}

bool QoSNegotiationRequestPayloadDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<QoSNegotiationRequestPayload *>(obj)!=nullptr;
}

const char **QoSNegotiationRequestPayloadDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *QoSNegotiationRequestPayloadDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int QoSNegotiationRequestPayloadDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int QoSNegotiationRequestPayloadDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *QoSNegotiationRequestPayloadDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int QoSNegotiationRequestPayloadDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *QoSNegotiationRequestPayloadDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **QoSNegotiationRequestPayloadDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *QoSNegotiationRequestPayloadDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int QoSNegotiationRequestPayloadDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationRequestPayload *pp = (QoSNegotiationRequestPayload *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *QoSNegotiationRequestPayloadDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationRequestPayload *pp = (QoSNegotiationRequestPayload *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string QoSNegotiationRequestPayloadDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationRequestPayload *pp = (QoSNegotiationRequestPayload *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool QoSNegotiationRequestPayloadDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationRequestPayload *pp = (QoSNegotiationRequestPayload *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *QoSNegotiationRequestPayloadDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *QoSNegotiationRequestPayloadDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationRequestPayload *pp = (QoSNegotiationRequestPayload *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(QoSNegotiationResponsePayload)

QoSNegotiationResponsePayload::QoSNegotiationResponsePayload(const char *name, short kind) : ::soqosmw::QoSNegotiationPayload(name,kind)
{
    this->resposeStatus = 0;
}

QoSNegotiationResponsePayload::QoSNegotiationResponsePayload(const QoSNegotiationResponsePayload& other) : ::soqosmw::QoSNegotiationPayload(other)
{
    copy(other);
}

QoSNegotiationResponsePayload::~QoSNegotiationResponsePayload()
{
}

QoSNegotiationResponsePayload& QoSNegotiationResponsePayload::operator=(const QoSNegotiationResponsePayload& other)
{
    if (this==&other) return *this;
    ::soqosmw::QoSNegotiationPayload::operator=(other);
    copy(other);
    return *this;
}

void QoSNegotiationResponsePayload::copy(const QoSNegotiationResponsePayload& other)
{
    this->resposeStatus = other.resposeStatus;
}

void QoSNegotiationResponsePayload::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::soqosmw::QoSNegotiationPayload::parsimPack(b);
    doParsimPacking(b,this->resposeStatus);
}

void QoSNegotiationResponsePayload::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::soqosmw::QoSNegotiationPayload::parsimUnpack(b);
    doParsimUnpacking(b,this->resposeStatus);
}

int QoSNegotiationResponsePayload::getResposeStatus() const
{
    return this->resposeStatus;
}

void QoSNegotiationResponsePayload::setResposeStatus(int resposeStatus)
{
    this->resposeStatus = resposeStatus;
}

class QoSNegotiationResponsePayloadDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    QoSNegotiationResponsePayloadDescriptor();
    virtual ~QoSNegotiationResponsePayloadDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(QoSNegotiationResponsePayloadDescriptor)

QoSNegotiationResponsePayloadDescriptor::QoSNegotiationResponsePayloadDescriptor() : omnetpp::cClassDescriptor("soqosmw::QoSNegotiationResponsePayload", "soqosmw::QoSNegotiationPayload")
{
    propertynames = nullptr;
}

QoSNegotiationResponsePayloadDescriptor::~QoSNegotiationResponsePayloadDescriptor()
{
    delete[] propertynames;
}

bool QoSNegotiationResponsePayloadDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<QoSNegotiationResponsePayload *>(obj)!=nullptr;
}

const char **QoSNegotiationResponsePayloadDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *QoSNegotiationResponsePayloadDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int QoSNegotiationResponsePayloadDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int QoSNegotiationResponsePayloadDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *QoSNegotiationResponsePayloadDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "resposeStatus",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int QoSNegotiationResponsePayloadDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "resposeStatus")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *QoSNegotiationResponsePayloadDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **QoSNegotiationResponsePayloadDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *QoSNegotiationResponsePayloadDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "soqosmw::QoSNegotiationResponseStatus";
            return nullptr;
        default: return nullptr;
    }
}

int QoSNegotiationResponsePayloadDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationResponsePayload *pp = (QoSNegotiationResponsePayload *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *QoSNegotiationResponsePayloadDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationResponsePayload *pp = (QoSNegotiationResponsePayload *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string QoSNegotiationResponsePayloadDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationResponsePayload *pp = (QoSNegotiationResponsePayload *)object; (void)pp;
    switch (field) {
        case 0: return enum2string(pp->getResposeStatus(), "soqosmw::QoSNegotiationResponseStatus");
        default: return "";
    }
}

bool QoSNegotiationResponsePayloadDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationResponsePayload *pp = (QoSNegotiationResponsePayload *)object; (void)pp;
    switch (field) {
        case 0: pp->setResposeStatus((soqosmw::QoSNegotiationResponseStatus)string2enum(value, "soqosmw::QoSNegotiationResponseStatus")); return true;
        default: return false;
    }
}

const char *QoSNegotiationResponsePayloadDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *QoSNegotiationResponsePayloadDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationResponsePayload *pp = (QoSNegotiationResponsePayload *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(QoSNegotiation)

QoSNegotiation::QoSNegotiation(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->type = 0;
    take(&(this->payload));
}

QoSNegotiation::QoSNegotiation(const QoSNegotiation& other) : ::omnetpp::cPacket(other)
{
    take(&(this->payload));
    copy(other);
}

QoSNegotiation::~QoSNegotiation()
{
    drop(&(this->payload));
}

QoSNegotiation& QoSNegotiation::operator=(const QoSNegotiation& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void QoSNegotiation::copy(const QoSNegotiation& other)
{
    this->type = other.type;
    this->providerDescription = other.providerDescription;
    this->clientDescription = other.clientDescription;
    this->payload = other.payload;
    this->payload.setName(other.payload.getName());
}

void QoSNegotiation::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->providerDescription);
    doParsimPacking(b,this->clientDescription);
    doParsimPacking(b,this->payload);
}

void QoSNegotiation::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->providerDescription);
    doParsimUnpacking(b,this->clientDescription);
    doParsimUnpacking(b,this->payload);
}

int QoSNegotiation::getType() const
{
    return this->type;
}

void QoSNegotiation::setType(int type)
{
    this->type = type;
}

EndpointDescription& QoSNegotiation::getProviderDescription()
{
    return this->providerDescription;
}

void QoSNegotiation::setProviderDescription(const EndpointDescription& providerDescription)
{
    this->providerDescription = providerDescription;
}

EndpointDescription& QoSNegotiation::getClientDescription()
{
    return this->clientDescription;
}

void QoSNegotiation::setClientDescription(const EndpointDescription& clientDescription)
{
    this->clientDescription = clientDescription;
}

QoSNegotiationPayload& QoSNegotiation::getPayload()
{
    return this->payload;
}

void QoSNegotiation::setPayload(const QoSNegotiationPayload& payload)
{
    this->payload = payload;
}

class QoSNegotiationDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    QoSNegotiationDescriptor();
    virtual ~QoSNegotiationDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(QoSNegotiationDescriptor)

QoSNegotiationDescriptor::QoSNegotiationDescriptor() : omnetpp::cClassDescriptor("soqosmw::QoSNegotiation", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

QoSNegotiationDescriptor::~QoSNegotiationDescriptor()
{
    delete[] propertynames;
}

bool QoSNegotiationDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<QoSNegotiation *>(obj)!=nullptr;
}

const char **QoSNegotiationDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *QoSNegotiationDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int QoSNegotiationDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int QoSNegotiationDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISCOWNEDOBJECT,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *QoSNegotiationDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "type",
        "providerDescription",
        "clientDescription",
        "payload",
    };
    return (field>=0 && field<4) ? fieldNames[field] : nullptr;
}

int QoSNegotiationDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "providerDescription")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "clientDescription")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "payload")==0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *QoSNegotiationDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "EndpointDescription",
        "EndpointDescription",
        "QoSNegotiationPayload",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : nullptr;
}

const char **QoSNegotiationDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *QoSNegotiationDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "soqosmw::QoSNegotiationMsgType";
            return nullptr;
        default: return nullptr;
    }
}

int QoSNegotiationDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiation *pp = (QoSNegotiation *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *QoSNegotiationDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiation *pp = (QoSNegotiation *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string QoSNegotiationDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiation *pp = (QoSNegotiation *)object; (void)pp;
    switch (field) {
        case 0: return enum2string(pp->getType(), "soqosmw::QoSNegotiationMsgType");
        case 1: {std::stringstream out; out << pp->getProviderDescription(); return out.str();}
        case 2: {std::stringstream out; out << pp->getClientDescription(); return out.str();}
        case 3: {std::stringstream out; out << pp->getPayload(); return out.str();}
        default: return "";
    }
}

bool QoSNegotiationDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiation *pp = (QoSNegotiation *)object; (void)pp;
    switch (field) {
        case 0: pp->setType((soqosmw::QoSNegotiationMsgType)string2enum(value, "soqosmw::QoSNegotiationMsgType")); return true;
        default: return false;
    }
}

const char *QoSNegotiationDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 1: return omnetpp::opp_typename(typeid(EndpointDescription));
        case 2: return omnetpp::opp_typename(typeid(EndpointDescription));
        case 3: return omnetpp::opp_typename(typeid(QoSNegotiationPayload));
        default: return nullptr;
    };
}

void *QoSNegotiationDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiation *pp = (QoSNegotiation *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getProviderDescription()); break;
        case 2: return (void *)(&pp->getClientDescription()); break;
        case 3: return (void *)static_cast<omnetpp::cObject *>(&pp->getPayload()); break;
        default: return nullptr;
    }
}

Register_Class(QoSNegotiationRequest)

QoSNegotiationRequest::QoSNegotiationRequest(const char *name, short kind) : ::soqosmw::QoSNegotiation(name,kind)
{
    this->setType(QoSNegotiationMsgType::QoS_Request);

    take(&(this->payload));
}

QoSNegotiationRequest::QoSNegotiationRequest(const QoSNegotiationRequest& other) : ::soqosmw::QoSNegotiation(other)
{
    take(&(this->payload));
    copy(other);
}

QoSNegotiationRequest::~QoSNegotiationRequest()
{
    drop(&(this->payload));
}

QoSNegotiationRequest& QoSNegotiationRequest::operator=(const QoSNegotiationRequest& other)
{
    if (this==&other) return *this;
    ::soqosmw::QoSNegotiation::operator=(other);
    copy(other);
    return *this;
}

void QoSNegotiationRequest::copy(const QoSNegotiationRequest& other)
{
    this->payload = other.payload;
    this->payload.setName(other.payload.getName());
}

void QoSNegotiationRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::soqosmw::QoSNegotiation::parsimPack(b);
    doParsimPacking(b,this->payload);
}

void QoSNegotiationRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::soqosmw::QoSNegotiation::parsimUnpack(b);
    doParsimUnpacking(b,this->payload);
}

QoSNegotiationRequestPayload& QoSNegotiationRequest::getPayload()
{
    return this->payload;
}

void QoSNegotiationRequest::setPayload(const QoSNegotiationRequestPayload& payload)
{
    this->payload = payload;
}

class QoSNegotiationRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    QoSNegotiationRequestDescriptor();
    virtual ~QoSNegotiationRequestDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(QoSNegotiationRequestDescriptor)

QoSNegotiationRequestDescriptor::QoSNegotiationRequestDescriptor() : omnetpp::cClassDescriptor("soqosmw::QoSNegotiationRequest", "soqosmw::QoSNegotiation")
{
    propertynames = nullptr;
}

QoSNegotiationRequestDescriptor::~QoSNegotiationRequestDescriptor()
{
    delete[] propertynames;
}

bool QoSNegotiationRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<QoSNegotiationRequest *>(obj)!=nullptr;
}

const char **QoSNegotiationRequestDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *QoSNegotiationRequestDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int QoSNegotiationRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int QoSNegotiationRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISCOWNEDOBJECT,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *QoSNegotiationRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "payload",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int QoSNegotiationRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "payload")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *QoSNegotiationRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "QoSNegotiationRequestPayload",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **QoSNegotiationRequestDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *QoSNegotiationRequestDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int QoSNegotiationRequestDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationRequest *pp = (QoSNegotiationRequest *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *QoSNegotiationRequestDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationRequest *pp = (QoSNegotiationRequest *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string QoSNegotiationRequestDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationRequest *pp = (QoSNegotiationRequest *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getPayload(); return out.str();}
        default: return "";
    }
}

bool QoSNegotiationRequestDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationRequest *pp = (QoSNegotiationRequest *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *QoSNegotiationRequestDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(QoSNegotiationRequestPayload));
        default: return nullptr;
    };
}

void *QoSNegotiationRequestDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationRequest *pp = (QoSNegotiationRequest *)object; (void)pp;
    switch (field) {
        case 0: return (void *)static_cast<omnetpp::cObject *>(&pp->getPayload()); break;
        default: return nullptr;
    }
}

Register_Class(QoSNegotiationResponse)

QoSNegotiationResponse::QoSNegotiationResponse(const char *name, short kind) : ::soqosmw::QoSNegotiation(name,kind)
{
    this->setType(QoSNegotiationMsgType::QoS_Response);

    take(&(this->payload));
}

QoSNegotiationResponse::QoSNegotiationResponse(const QoSNegotiationResponse& other) : ::soqosmw::QoSNegotiation(other)
{
    take(&(this->payload));
    copy(other);
}

QoSNegotiationResponse::~QoSNegotiationResponse()
{
    drop(&(this->payload));
}

QoSNegotiationResponse& QoSNegotiationResponse::operator=(const QoSNegotiationResponse& other)
{
    if (this==&other) return *this;
    ::soqosmw::QoSNegotiation::operator=(other);
    copy(other);
    return *this;
}

void QoSNegotiationResponse::copy(const QoSNegotiationResponse& other)
{
    this->payload = other.payload;
    this->payload.setName(other.payload.getName());
}

void QoSNegotiationResponse::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::soqosmw::QoSNegotiation::parsimPack(b);
    doParsimPacking(b,this->payload);
}

void QoSNegotiationResponse::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::soqosmw::QoSNegotiation::parsimUnpack(b);
    doParsimUnpacking(b,this->payload);
}

QoSNegotiationResponsePayload& QoSNegotiationResponse::getPayload()
{
    return this->payload;
}

void QoSNegotiationResponse::setPayload(const QoSNegotiationResponsePayload& payload)
{
    this->payload = payload;
}

class QoSNegotiationResponseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    QoSNegotiationResponseDescriptor();
    virtual ~QoSNegotiationResponseDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(QoSNegotiationResponseDescriptor)

QoSNegotiationResponseDescriptor::QoSNegotiationResponseDescriptor() : omnetpp::cClassDescriptor("soqosmw::QoSNegotiationResponse", "soqosmw::QoSNegotiation")
{
    propertynames = nullptr;
}

QoSNegotiationResponseDescriptor::~QoSNegotiationResponseDescriptor()
{
    delete[] propertynames;
}

bool QoSNegotiationResponseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<QoSNegotiationResponse *>(obj)!=nullptr;
}

const char **QoSNegotiationResponseDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *QoSNegotiationResponseDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int QoSNegotiationResponseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int QoSNegotiationResponseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISCOWNEDOBJECT,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *QoSNegotiationResponseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "payload",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int QoSNegotiationResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "payload")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *QoSNegotiationResponseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "QoSNegotiationResponsePayload",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **QoSNegotiationResponseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *QoSNegotiationResponseDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int QoSNegotiationResponseDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationResponse *pp = (QoSNegotiationResponse *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *QoSNegotiationResponseDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationResponse *pp = (QoSNegotiationResponse *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string QoSNegotiationResponseDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationResponse *pp = (QoSNegotiationResponse *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getPayload(); return out.str();}
        default: return "";
    }
}

bool QoSNegotiationResponseDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationResponse *pp = (QoSNegotiationResponse *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *QoSNegotiationResponseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(QoSNegotiationResponsePayload));
        default: return nullptr;
    };
}

void *QoSNegotiationResponseDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationResponse *pp = (QoSNegotiationResponse *)object; (void)pp;
    switch (field) {
        case 0: return (void *)static_cast<omnetpp::cObject *>(&pp->getPayload()); break;
        default: return nullptr;
    }
}

Register_Class(QoSConnectionEstablish)

QoSConnectionEstablish::QoSConnectionEstablish(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->type = 0;
}

QoSConnectionEstablish::QoSConnectionEstablish(const QoSConnectionEstablish& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

QoSConnectionEstablish::~QoSConnectionEstablish()
{
}

QoSConnectionEstablish& QoSConnectionEstablish::operator=(const QoSConnectionEstablish& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void QoSConnectionEstablish::copy(const QoSConnectionEstablish& other)
{
    this->type = other.type;
    this->providerDescription = other.providerDescription;
    this->clientDescription = other.clientDescription;
}

void QoSConnectionEstablish::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->providerDescription);
    doParsimPacking(b,this->clientDescription);
}

void QoSConnectionEstablish::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->providerDescription);
    doParsimUnpacking(b,this->clientDescription);
}

int QoSConnectionEstablish::getType() const
{
    return this->type;
}

void QoSConnectionEstablish::setType(int type)
{
    this->type = type;
}

EndpointDescription& QoSConnectionEstablish::getProviderDescription()
{
    return this->providerDescription;
}

void QoSConnectionEstablish::setProviderDescription(const EndpointDescription& providerDescription)
{
    this->providerDescription = providerDescription;
}

EndpointDescription& QoSConnectionEstablish::getClientDescription()
{
    return this->clientDescription;
}

void QoSConnectionEstablish::setClientDescription(const EndpointDescription& clientDescription)
{
    this->clientDescription = clientDescription;
}

class QoSConnectionEstablishDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    QoSConnectionEstablishDescriptor();
    virtual ~QoSConnectionEstablishDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(QoSConnectionEstablishDescriptor)

QoSConnectionEstablishDescriptor::QoSConnectionEstablishDescriptor() : omnetpp::cClassDescriptor("soqosmw::QoSConnectionEstablish", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

QoSConnectionEstablishDescriptor::~QoSConnectionEstablishDescriptor()
{
    delete[] propertynames;
}

bool QoSConnectionEstablishDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<QoSConnectionEstablish *>(obj)!=nullptr;
}

const char **QoSConnectionEstablishDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *QoSConnectionEstablishDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int QoSConnectionEstablishDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int QoSConnectionEstablishDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *QoSConnectionEstablishDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "type",
        "providerDescription",
        "clientDescription",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int QoSConnectionEstablishDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "providerDescription")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "clientDescription")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *QoSConnectionEstablishDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "EndpointDescription",
        "EndpointDescription",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **QoSConnectionEstablishDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *QoSConnectionEstablishDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "soqosmw::QoSConnectionEstablishMsgType";
            return nullptr;
        default: return nullptr;
    }
}

int QoSConnectionEstablishDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    QoSConnectionEstablish *pp = (QoSConnectionEstablish *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *QoSConnectionEstablishDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QoSConnectionEstablish *pp = (QoSConnectionEstablish *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string QoSConnectionEstablishDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QoSConnectionEstablish *pp = (QoSConnectionEstablish *)object; (void)pp;
    switch (field) {
        case 0: return enum2string(pp->getType(), "soqosmw::QoSConnectionEstablishMsgType");
        case 1: {std::stringstream out; out << pp->getProviderDescription(); return out.str();}
        case 2: {std::stringstream out; out << pp->getClientDescription(); return out.str();}
        default: return "";
    }
}

bool QoSConnectionEstablishDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    QoSConnectionEstablish *pp = (QoSConnectionEstablish *)object; (void)pp;
    switch (field) {
        case 0: pp->setType((soqosmw::QoSConnectionEstablishMsgType)string2enum(value, "soqosmw::QoSConnectionEstablishMsgType")); return true;
        default: return false;
    }
}

const char *QoSConnectionEstablishDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 1: return omnetpp::opp_typename(typeid(EndpointDescription));
        case 2: return omnetpp::opp_typename(typeid(EndpointDescription));
        default: return nullptr;
    };
}

void *QoSConnectionEstablishDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    QoSConnectionEstablish *pp = (QoSConnectionEstablish *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getProviderDescription()); break;
        case 2: return (void *)(&pp->getClientDescription()); break;
        default: return nullptr;
    }
}

} // namespace soqosmw

