/*
 * QoSGroups.h
 *
 *  Created on: 02.11.2017
 *      Author: skrec
 */

#ifndef SOQOSMW_QOSMANAGEMENT_QOSGROUPS_H_
#define SOQOSMW_QOSMANAGEMENT_QOSGROUPS_H_



namespace soqosmw {

//Groups of QoS Requirements
typedef enum QoSGroups {
    QoSGroup_RT = 0, // RealTime Requirements --> AVB / TSN
    QoSGroup_STD = 1, // Standard Requirements --> BE
    QoSGroup_WEB = 2, // Web Requirements --> HTTP
} QoSGroups_t;

} /* namespace soqosmw */


#endif /* SOQOSMW_QOSMANAGEMENT_QOSGROUPS_H_ */
