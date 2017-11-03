//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

cplusplus {{
    #include "soqosmw/base/EndpointDescription.h"
    #include "soqosmw/qosmanagement/QoSGroups.h"
    using namespace soqosmw;
}}
class noncobject EndpointDescription;
class noncobject QoSGroups_t;

namespace soqosmw;

//Type of Negotiation message for @see QoSNegotiation
enum QoSNegotiationMsgType{
    QoS_Request 	= 0;
    QoS_Response 	= 1;
}

//Type of Connection Establish message for @see QoSConnectionEstablish
enum QoSConnectionEstablishMsgType{
    Establish_Request 	= 0;
    Establish_Success 	= 1;
    Establish_Failure 	= 2;
}

//Type of Negotiation response payload status @see QoSNegotiationResponsePayload
enum QoSNegotiationResponseStatus{
 	QoS_ResponseStatusSuccess	= 0;
 	QoS_ResponseStatusFailure	= 1;
}

//common parameters of qos negotiation
packet QoSNegotiationPayload {
    QoSGroups_t		qosGroup;
}

//special parameters for requests
packet QoSNegotiationRequestPayload extends QoSNegotiationPayload {
    
}

//special parameters for response
packet QoSNegotiationResponsePayload extends QoSNegotiationPayload {
    int		resposeStatus @enum(QoSNegotiationResponseStatus);
}

packet QoSNegotiation {
    int 					type @enum(QoSNegotiationMsgType);
    EndpointDescription 	providerDescription;
    EndpointDescription		clientDescription;
    QoSNegotiationPayload 	payload;
}

packet QoSNegotiationRequest extends QoSNegotiation{
    type = QoSNegotiationMsgType::QoS_Request;
    QoSNegotiationRequestPayload payload;
}

packet QoSNegotiationResponse extends QoSNegotiation{
    type = QoSNegotiationMsgType::QoS_Response;
    QoSNegotiationResponsePayload payload;
}

packet QoSConnectionEstablish {
    int 					type @enum(QoSConnectionEstablishMsgType);
    EndpointDescription 	providerDescription;
    EndpointDescription		clientDescription;
}

