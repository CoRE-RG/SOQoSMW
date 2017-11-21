//
// Generated file, do not edit! Created by nedtool 5.1 from soqosmw/messages/QoSNegotiationProtocol/QoSNegotiationProtocol.msg.
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
#include "QoSNegotiationProtocol_m.h"

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
    e->insert(RT, "RT");
    e->insert(STD, "STD");
    e->insert(WEB, "WEB");
)

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("soqosmw::QoSNegotiationMsgType");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("soqosmw::QoSNegotiationMsgType"));
    e->insert(QoS_Request, "QoS_Request");
    e->insert(QoS_Response, "QoS_Response");
    e->insert(QoS_Establish, "QoS_Establish");
    e->insert(QoS_Finalise, "QoS_Finalise");
)

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("soqosmw::QoSNegotiationStatus");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("soqosmw::QoSNegotiationStatus"));
    e->insert(Failure, "Failure");
    e->insert(Success, "Success");
)

Register_Class(QoSNegotiationProtocol)

QoSNegotiationProtocol::QoSNegotiationProtocol(const char *name, short kind) : ::soqosmw::Envelope(name,kind)
{
    this->setProtocol(SOQoSMWProtocols::QOSNEGOTIATIONPROTOCOL);

    this->messageType = 0;
    this->qosClass = 0;
}

QoSNegotiationProtocol::QoSNegotiationProtocol(const QoSNegotiationProtocol& other) : ::soqosmw::Envelope(other)
{
    copy(other);
}

QoSNegotiationProtocol::~QoSNegotiationProtocol()
{
}

QoSNegotiationProtocol& QoSNegotiationProtocol::operator=(const QoSNegotiationProtocol& other)
{
    if (this==&other) return *this;
    ::soqosmw::Envelope::operator=(other);
    copy(other);
    return *this;
}

void QoSNegotiationProtocol::copy(const QoSNegotiationProtocol& other)
{
    this->messageType = other.messageType;
    this->qosClass = other.qosClass;
}

void QoSNegotiationProtocol::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::soqosmw::Envelope::parsimPack(b);
    doParsimPacking(b,this->messageType);
    doParsimPacking(b,this->qosClass);
}

void QoSNegotiationProtocol::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::soqosmw::Envelope::parsimUnpack(b);
    doParsimUnpacking(b,this->messageType);
    doParsimUnpacking(b,this->qosClass);
}

int QoSNegotiationProtocol::getMessageType() const
{
    return this->messageType;
}

void QoSNegotiationProtocol::setMessageType(int messageType)
{
    this->messageType = messageType;
}

int QoSNegotiationProtocol::getQosClass() const
{
    return this->qosClass;
}

void QoSNegotiationProtocol::setQosClass(int qosClass)
{
    this->qosClass = qosClass;
}

class QoSNegotiationProtocolDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    QoSNegotiationProtocolDescriptor();
    virtual ~QoSNegotiationProtocolDescriptor();

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

Register_ClassDescriptor(QoSNegotiationProtocolDescriptor)

QoSNegotiationProtocolDescriptor::QoSNegotiationProtocolDescriptor() : omnetpp::cClassDescriptor("soqosmw::QoSNegotiationProtocol", "soqosmw::Envelope")
{
    propertynames = nullptr;
}

QoSNegotiationProtocolDescriptor::~QoSNegotiationProtocolDescriptor()
{
    delete[] propertynames;
}

bool QoSNegotiationProtocolDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<QoSNegotiationProtocol *>(obj)!=nullptr;
}

const char **QoSNegotiationProtocolDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *QoSNegotiationProtocolDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int QoSNegotiationProtocolDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int QoSNegotiationProtocolDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *QoSNegotiationProtocolDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "messageType",
        "qosClass",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int QoSNegotiationProtocolDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageType")==0) return base+0;
    if (fieldName[0]=='q' && strcmp(fieldName, "qosClass")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *QoSNegotiationProtocolDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **QoSNegotiationProtocolDescriptor::getFieldPropertyNames(int field) const
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
        case 1: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *QoSNegotiationProtocolDescriptor::getFieldProperty(int field, const char *propertyname) const
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
        case 1:
            if (!strcmp(propertyname,"enum")) return "soqosmw::QoSGroups";
            return nullptr;
        default: return nullptr;
    }
}

int QoSNegotiationProtocolDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationProtocol *pp = (QoSNegotiationProtocol *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *QoSNegotiationProtocolDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationProtocol *pp = (QoSNegotiationProtocol *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string QoSNegotiationProtocolDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationProtocol *pp = (QoSNegotiationProtocol *)object; (void)pp;
    switch (field) {
        case 0: return enum2string(pp->getMessageType(), "soqosmw::QoSNegotiationMsgType");
        case 1: return enum2string(pp->getQosClass(), "soqosmw::QoSGroups");
        default: return "";
    }
}

bool QoSNegotiationProtocolDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationProtocol *pp = (QoSNegotiationProtocol *)object; (void)pp;
    switch (field) {
        case 0: pp->setMessageType((soqosmw::QoSNegotiationMsgType)string2enum(value, "soqosmw::QoSNegotiationMsgType")); return true;
        case 1: pp->setQosClass((soqosmw::QoSGroups)string2enum(value, "soqosmw::QoSGroups")); return true;
        default: return false;
    }
}

const char *QoSNegotiationProtocolDescriptor::getFieldStructName(int field) const
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

void *QoSNegotiationProtocolDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationProtocol *pp = (QoSNegotiationProtocol *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(QoSNegotiationRequest)

QoSNegotiationRequest::QoSNegotiationRequest(const char *name, short kind) : ::soqosmw::QoSNegotiationProtocol(name,kind)
{
    this->setMessageType(QoSNegotiationMsgType::QoS_Request);
}

QoSNegotiationRequest::QoSNegotiationRequest(const QoSNegotiationRequest& other) : ::soqosmw::QoSNegotiationProtocol(other)
{
    copy(other);
}

QoSNegotiationRequest::~QoSNegotiationRequest()
{
}

QoSNegotiationRequest& QoSNegotiationRequest::operator=(const QoSNegotiationRequest& other)
{
    if (this==&other) return *this;
    ::soqosmw::QoSNegotiationProtocol::operator=(other);
    copy(other);
    return *this;
}

void QoSNegotiationRequest::copy(const QoSNegotiationRequest& other)
{
}

void QoSNegotiationRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::soqosmw::QoSNegotiationProtocol::parsimPack(b);
}

void QoSNegotiationRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::soqosmw::QoSNegotiationProtocol::parsimUnpack(b);
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

QoSNegotiationRequestDescriptor::QoSNegotiationRequestDescriptor() : omnetpp::cClassDescriptor("soqosmw::QoSNegotiationRequest", "soqosmw::QoSNegotiationProtocol")
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
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int QoSNegotiationRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *QoSNegotiationRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int QoSNegotiationRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
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
    return nullptr;
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
    return nullptr;
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
        default: return nullptr;
    }
}

Register_Class(QoSNegotiationResponse)

QoSNegotiationResponse::QoSNegotiationResponse(const char *name, short kind) : ::soqosmw::QoSNegotiationProtocol(name,kind)
{
    this->setMessageType(QoSNegotiationMsgType::QoS_Response);

    this->responseStatus = 0;
}

QoSNegotiationResponse::QoSNegotiationResponse(const QoSNegotiationResponse& other) : ::soqosmw::QoSNegotiationProtocol(other)
{
    copy(other);
}

QoSNegotiationResponse::~QoSNegotiationResponse()
{
}

QoSNegotiationResponse& QoSNegotiationResponse::operator=(const QoSNegotiationResponse& other)
{
    if (this==&other) return *this;
    ::soqosmw::QoSNegotiationProtocol::operator=(other);
    copy(other);
    return *this;
}

void QoSNegotiationResponse::copy(const QoSNegotiationResponse& other)
{
    this->responseStatus = other.responseStatus;
}

void QoSNegotiationResponse::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::soqosmw::QoSNegotiationProtocol::parsimPack(b);
    doParsimPacking(b,this->responseStatus);
}

void QoSNegotiationResponse::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::soqosmw::QoSNegotiationProtocol::parsimUnpack(b);
    doParsimUnpacking(b,this->responseStatus);
}

int QoSNegotiationResponse::getResponseStatus() const
{
    return this->responseStatus;
}

void QoSNegotiationResponse::setResponseStatus(int responseStatus)
{
    this->responseStatus = responseStatus;
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

QoSNegotiationResponseDescriptor::QoSNegotiationResponseDescriptor() : omnetpp::cClassDescriptor("soqosmw::QoSNegotiationResponse", "soqosmw::QoSNegotiationProtocol")
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
        FD_ISEDITABLE,
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
        "responseStatus",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int QoSNegotiationResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "responseStatus")==0) return base+0;
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
        "int",
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
        case 0: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
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
        case 0:
            if (!strcmp(propertyname,"enum")) return "soqosmw::QoSNegotiationStatus";
            return nullptr;
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
        case 0: return enum2string(pp->getResponseStatus(), "soqosmw::QoSNegotiationStatus");
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
        case 0: pp->setResponseStatus((soqosmw::QoSNegotiationStatus)string2enum(value, "soqosmw::QoSNegotiationStatus")); return true;
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
        default: return nullptr;
    }
}

Register_Class(QoSNegotiationEstablish)

QoSNegotiationEstablish::QoSNegotiationEstablish(const char *name, short kind) : ::soqosmw::QoSNegotiationProtocol(name,kind)
{
    this->setMessageType(QoSNegotiationMsgType::QoS_Establish);
}

QoSNegotiationEstablish::QoSNegotiationEstablish(const QoSNegotiationEstablish& other) : ::soqosmw::QoSNegotiationProtocol(other)
{
    copy(other);
}

QoSNegotiationEstablish::~QoSNegotiationEstablish()
{
}

QoSNegotiationEstablish& QoSNegotiationEstablish::operator=(const QoSNegotiationEstablish& other)
{
    if (this==&other) return *this;
    ::soqosmw::QoSNegotiationProtocol::operator=(other);
    copy(other);
    return *this;
}

void QoSNegotiationEstablish::copy(const QoSNegotiationEstablish& other)
{
}

void QoSNegotiationEstablish::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::soqosmw::QoSNegotiationProtocol::parsimPack(b);
}

void QoSNegotiationEstablish::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::soqosmw::QoSNegotiationProtocol::parsimUnpack(b);
}

class QoSNegotiationEstablishDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    QoSNegotiationEstablishDescriptor();
    virtual ~QoSNegotiationEstablishDescriptor();

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

Register_ClassDescriptor(QoSNegotiationEstablishDescriptor)

QoSNegotiationEstablishDescriptor::QoSNegotiationEstablishDescriptor() : omnetpp::cClassDescriptor("soqosmw::QoSNegotiationEstablish", "soqosmw::QoSNegotiationProtocol")
{
    propertynames = nullptr;
}

QoSNegotiationEstablishDescriptor::~QoSNegotiationEstablishDescriptor()
{
    delete[] propertynames;
}

bool QoSNegotiationEstablishDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<QoSNegotiationEstablish *>(obj)!=nullptr;
}

const char **QoSNegotiationEstablishDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *QoSNegotiationEstablishDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int QoSNegotiationEstablishDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int QoSNegotiationEstablishDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *QoSNegotiationEstablishDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int QoSNegotiationEstablishDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *QoSNegotiationEstablishDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **QoSNegotiationEstablishDescriptor::getFieldPropertyNames(int field) const
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

const char *QoSNegotiationEstablishDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int QoSNegotiationEstablishDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationEstablish *pp = (QoSNegotiationEstablish *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *QoSNegotiationEstablishDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationEstablish *pp = (QoSNegotiationEstablish *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string QoSNegotiationEstablishDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationEstablish *pp = (QoSNegotiationEstablish *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool QoSNegotiationEstablishDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationEstablish *pp = (QoSNegotiationEstablish *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *QoSNegotiationEstablishDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *QoSNegotiationEstablishDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationEstablish *pp = (QoSNegotiationEstablish *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(QoSNegotiationFinalise)

QoSNegotiationFinalise::QoSNegotiationFinalise(const char *name, short kind) : ::soqosmw::QoSNegotiationProtocol(name,kind)
{
    this->setMessageType(QoSNegotiationMsgType::QoS_Finalise);
}

QoSNegotiationFinalise::QoSNegotiationFinalise(const QoSNegotiationFinalise& other) : ::soqosmw::QoSNegotiationProtocol(other)
{
    copy(other);
}

QoSNegotiationFinalise::~QoSNegotiationFinalise()
{
}

QoSNegotiationFinalise& QoSNegotiationFinalise::operator=(const QoSNegotiationFinalise& other)
{
    if (this==&other) return *this;
    ::soqosmw::QoSNegotiationProtocol::operator=(other);
    copy(other);
    return *this;
}

void QoSNegotiationFinalise::copy(const QoSNegotiationFinalise& other)
{
}

void QoSNegotiationFinalise::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::soqosmw::QoSNegotiationProtocol::parsimPack(b);
}

void QoSNegotiationFinalise::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::soqosmw::QoSNegotiationProtocol::parsimUnpack(b);
}

class QoSNegotiationFinaliseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    QoSNegotiationFinaliseDescriptor();
    virtual ~QoSNegotiationFinaliseDescriptor();

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

Register_ClassDescriptor(QoSNegotiationFinaliseDescriptor)

QoSNegotiationFinaliseDescriptor::QoSNegotiationFinaliseDescriptor() : omnetpp::cClassDescriptor("soqosmw::QoSNegotiationFinalise", "soqosmw::QoSNegotiationProtocol")
{
    propertynames = nullptr;
}

QoSNegotiationFinaliseDescriptor::~QoSNegotiationFinaliseDescriptor()
{
    delete[] propertynames;
}

bool QoSNegotiationFinaliseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<QoSNegotiationFinalise *>(obj)!=nullptr;
}

const char **QoSNegotiationFinaliseDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *QoSNegotiationFinaliseDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int QoSNegotiationFinaliseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int QoSNegotiationFinaliseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *QoSNegotiationFinaliseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int QoSNegotiationFinaliseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *QoSNegotiationFinaliseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **QoSNegotiationFinaliseDescriptor::getFieldPropertyNames(int field) const
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

const char *QoSNegotiationFinaliseDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int QoSNegotiationFinaliseDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationFinalise *pp = (QoSNegotiationFinalise *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *QoSNegotiationFinaliseDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationFinalise *pp = (QoSNegotiationFinalise *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string QoSNegotiationFinaliseDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationFinalise *pp = (QoSNegotiationFinalise *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool QoSNegotiationFinaliseDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationFinalise *pp = (QoSNegotiationFinalise *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *QoSNegotiationFinaliseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *QoSNegotiationFinaliseDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    QoSNegotiationFinalise *pp = (QoSNegotiationFinalise *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

} // namespace soqosmw

