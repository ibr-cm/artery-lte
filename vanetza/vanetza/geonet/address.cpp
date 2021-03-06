#include "address.hpp"
#include "serialization.hpp"

namespace vanetza
{
namespace geonet
{

const std::size_t Address::length_bytes;
const uint16_t manually_configured_mask = 0x8000;
const uint16_t station_type_mask = 0x7c00;
const uint16_t country_code_mask = 0x03ff;
const unsigned station_type_shift = 10;

Address::Address() :
    m_manually_configured(false),
    m_station_type(StationType::UNKNOWN),
    m_country_code(0)
{
}

Address::Address(const MacAddress& addr) :
    m_manually_configured(false),
    m_station_type(StationType::UNKNOWN),
    m_country_code(0),
    m_mid(addr)
{
}

bool Address::operator==(const Address& other) const
{
    return (this->m_manually_configured == other.m_manually_configured &&
        this->m_station_type == other.m_station_type &&
        this->m_country_code == other.m_country_code &&
        this->m_mid == other.m_mid);
}

bool Address::operator!=(const Address& other) const
{
    return !(*this == other);
}

void serialize(const Address& addr, OutputArchive& ar)
{
    uint16_t manuallyConfiguredAndTypeAndCountryCode = addr.country_code().raw();
    manuallyConfiguredAndTypeAndCountryCode |=
        (static_cast<uint16_t>(addr.station_type()) << station_type_shift) & station_type_mask;
    manuallyConfiguredAndTypeAndCountryCode |=
        addr.is_manually_configured() ? manually_configured_mask : 0x0000;
    serialize(host_cast(manuallyConfiguredAndTypeAndCountryCode), ar);
    serialize(addr.mid(), ar);
}

void serialize(const MacAddress& addr, OutputArchive& ar)
{
    for (uint8_t octet : addr.octets) {
        ar << octet;
    }
}

void deserialize(Address& addr, InputArchive& ar)
{
    uint16_t tmp;
    deserialize(tmp, ar);
    addr.is_manually_configured((tmp & manually_configured_mask) != 0);
    addr.country_code(tmp & country_code_mask);
    addr.station_type(static_cast<StationType>((tmp & station_type_mask) >> station_type_shift));
    MacAddress mid;
    deserialize(mid, ar);
    addr.mid(mid);
}

void deserialize(MacAddress& addr, InputArchive& ar)
{
    for (uint8_t& octet : addr.octets) {
        ar >> octet;
    }
}

} // namespace geonet
} // namespace vanetza

