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

#ifndef VEHICLETELEMETRYSERVICE_H_
#define VEHICLETELEMETRYSERVICE_H_

#include "ItsG5Service.h"

/**
 * @brief
 * A vehicle service that sends telemetry data to a backend service.
 *
 * @author Julian Timpner
 */
class VehicleTelemetryService : public ItsG5Service
{
    public:
        VehicleTelemetryService();
        virtual ~VehicleTelemetryService();

        void indicate(const vanetza::btp::DataIndication&, cPacket*) override;
        void trigger() override;
        void receiveSignal(cComponent*, simsignal_t, bool) override;

    protected:
        void initialize() override;
        void finish() override;
        void handleMessage(cMessage*) override;

    private:
        bool debug;
        simtime_t lastMessageSent;
        Coord lastMessagePosition;
        simtime_t lteTransmissionInterval;
        double lteTransmissionMaxDistance;
};

#endif /* VEHICLETELEMETRYSERVICE_H_ */
