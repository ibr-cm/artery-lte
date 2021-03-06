#ifndef SERVERAPP_H_
#define SERVERAPP_H_

#include <omnetpp.h>
#include "ApplicationBase.h"
#include "INETDefs.h"
#include "UDPSocket.h"
#include "IPv4Address.h"

#include "veins/modules/mobility/traci/TraCIScenarioManager.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"
#include "veins/modules/mobility/traci/TraCIMobility.h"
#include <artery/database/ServerDatabase.h>
/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using Veins::TraCIMobility;
using Veins::TraCICommandInterface;
using Veins::TraCIScenarioManager;
using Veins::TraCIScenarioManagerAccess;

/**
 * @brief
 * A backend application that processes telemetry information received from vehicles, as well as ground truth data from TraCI.
 *
 * @author Julian Timpner
 */
class ServerApp: public ApplicationBase {
protected:
    UDPSocket socket;
    long receivedMessagesViaLte;
    long receivedMessagesViaDsrc;
    long receivedBytes;
    int udpOut;
    int udpIn;

    TraCIScenarioManager* scenarioManager;
    TraCICommandInterface* traci;
    TraCICommandInterface::Vehicle* traciVehicle;

    ServerDatabase *db;
    sql::Connection *con;

    std::set<std::string> insertedVehicles;
    std::set<std::pair<std::string, int32_t > > insertedSections;

public:
    ServerApp();
    virtual ~ServerApp();

    virtual int numInitStages() const {
        return 4;
    }
    virtual void initialize(int stage);
    virtual void finish();
    virtual void handleMessageWhenUp(cMessage *msg);

    virtual bool handleNodeStart(IDoneCallback *doneCallback);
    virtual bool handleNodeShutdown(IDoneCallback *doneCallback);
    virtual void handleNodeCrash();

private:
    bool debug;
    simtime_t traciLogInterval;
    void storeTraCISnapshot();
    void storeVehicle(const std::string& vehicleId, Veins::TraCICommandInterface::Vehicle& v);
    void storeSection(const std::string roadId, const int32_t laneIndex);
    void storeSection(const std::pair<std::string, int32_t>& section);
};

#endif /* SERVERAPP_H_ */
