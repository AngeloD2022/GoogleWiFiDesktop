//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     Welcome data = nlohmann::json::parse(jsonString);

#pragma once

#include "json.hpp"

#include <boost/optional.hpp>
#include <stdexcept>
#include <regex>

#ifndef NLOHMANN_OPT_HELPER
#define NLOHMANN_OPT_HELPER
namespace nlohmann {
    template<typename T>
    struct adl_serializer<std::shared_ptr<T>> {
        static void to_json(json &j, const std::shared_ptr<T> &opt) {
            if (!opt) j = nullptr; else j = *opt;
        }

        static std::shared_ptr<T> from_json(const json &j) {
            if (j.is_null()) return std::unique_ptr<T>(); else return std::unique_ptr<T>(new T(j.get<T>()));
        }
    };
}
#endif

namespace SystemDevices {
    using nlohmann::json;

    inline json get_untyped(const json &j, const char *property) {
        if (j.find(property) != j.end()) {
            return j.at(property).get<json>();
        }
        return json();
    }

    inline json get_untyped(const json &j, std::string property) {
        return get_untyped(j, property.data());
    }

    template<typename T>
    inline std::shared_ptr<T> get_optional(const json &j, const char *property) {
        if (j.find(property) != j.end()) {
            return j.at(property).get<std::shared_ptr<T>>();
        }
        return std::shared_ptr<T>();
    }

    template<typename T>
    inline std::shared_ptr<T> get_optional(const json &j, std::string property) {
        return get_optional<T>(j, property.data());
    }

    enum class ConnectionType : int {
        WIRED, WIRELESS
    };

    enum class WirelessBand : int {
        BAND_2400__MHZ, BAND_5000__MHZ, NOT_APPLICABLE
    };

    class Station {
    public:
        Station() = default;

        virtual ~Station() = default;

    private:
        std::string id;
        std::string friendly_name;
        std::shared_ptr<std::string> friendly_type;
        ConnectionType connection_type;
        std::string ap_id;
        WirelessBand wireless_band;
        std::shared_ptr<std::string> unfiltered_friendly_type;
        std::shared_ptr<std::string> unfiltered_curated_oui_name;
        std::string automatic_friendly_name;
        std::shared_ptr<std::string> curated_oui_name;
        std::shared_ptr<std::vector<std::string>> ip_addresses;
        std::shared_ptr<bool> connected;
        std::shared_ptr<std::string> ip_address;
        std::shared_ptr<std::string> station_type;

    public:
        const std::string &get_id() const { return id; }

        std::string &get_mutable_id() { return id; }

        void set_id(const std::string &value) { this->id = value; }

        const std::string &get_friendly_name() const { return friendly_name; }

        std::string &get_mutable_friendly_name() { return friendly_name; }

        void set_friendly_name(const std::string &value) { this->friendly_name = value; }

        std::shared_ptr<std::string> get_friendly_type() const { return friendly_type; }

        void set_friendly_type(std::shared_ptr<std::string> value) { this->friendly_type = value; }

        const ConnectionType &get_connection_type() const { return connection_type; }

        ConnectionType &get_mutable_connection_type() { return connection_type; }

        void set_connection_type(const ConnectionType &value) { this->connection_type = value; }

        const std::string &get_ap_id() const { return ap_id; }

        std::string &get_mutable_ap_id() { return ap_id; }

        void set_ap_id(const std::string &value) { this->ap_id = value; }

        const WirelessBand &get_wireless_band() const { return wireless_band; }

        WirelessBand &get_mutable_wireless_band() { return wireless_band; }

        void set_wireless_band(const WirelessBand &value) { this->wireless_band = value; }

        std::shared_ptr<std::string> get_unfiltered_friendly_type() const { return unfiltered_friendly_type; }

        void
        set_unfiltered_friendly_type(std::shared_ptr<std::string> value) { this->unfiltered_friendly_type = value; }

        std::shared_ptr<std::string> get_unfiltered_curated_oui_name() const { return unfiltered_curated_oui_name; }

        void set_unfiltered_curated_oui_name(
                std::shared_ptr<std::string> value) { this->unfiltered_curated_oui_name = value; }

        const std::string &get_automatic_friendly_name() const { return automatic_friendly_name; }

        std::string &get_mutable_automatic_friendly_name() { return automatic_friendly_name; }

        void set_automatic_friendly_name(const std::string &value) { this->automatic_friendly_name = value; }

        std::shared_ptr<std::string> get_curated_oui_name() const { return curated_oui_name; }

        void set_curated_oui_name(std::shared_ptr<std::string> value) { this->curated_oui_name = value; }

        std::shared_ptr<std::vector<std::string>> get_ip_addresses() const { return ip_addresses; }

        void set_ip_addresses(std::shared_ptr<std::vector<std::string>> value) { this->ip_addresses = value; }

        std::shared_ptr<bool> get_connected() const { return connected; }

        void set_connected(std::shared_ptr<bool> value) { this->connected = value; }

        std::shared_ptr<std::string> get_ip_address() const { return ip_address; }

        void set_ip_address(std::shared_ptr<std::string> value) { this->ip_address = value; }

        std::shared_ptr<std::string> get_station_type() const { return station_type; }

        void set_station_type(std::shared_ptr<std::string> value) { this->station_type = value; }
    };

    class Welcome {
    public:
        Welcome() = default;

        virtual ~Welcome() = default;

    private:
        std::vector<Station> stations;

    public:
        const std::vector<Station> &get_stations() const { return stations; }

        std::vector<Station> &get_mutable_stations() { return stations; }

        void set_stations(const std::vector<Station> &value) { this->stations = value; }
    };
}

namespace nlohmann {
    void from_json(const json &j, SystemDevices::Station &x);

    void to_json(json &j, const SystemDevices::Station &x);

    void from_json(const json &j, SystemDevices::Welcome &x);

    void to_json(json &j, const SystemDevices::Welcome &x);

    void from_json(const json &j, SystemDevices::ConnectionType &x);

    void to_json(json &j, const SystemDevices::ConnectionType &x);

    void from_json(const json &j, SystemDevices::WirelessBand &x);

    void to_json(json &j, const SystemDevices::WirelessBand &x);

    inline void from_json(const json &j, SystemDevices::Station &x) {
        x.set_id(j.at("id").get<std::string>());
        x.set_friendly_name(j.at("friendlyName").get<std::string>());
        x.set_friendly_type(SystemDevices::get_optional<std::string>(j, "friendlyType"));
        x.set_connection_type(j.at("connectionType").get<SystemDevices::ConnectionType>());
        x.set_ap_id(j.at("apId").get<std::string>());
        x.set_wireless_band(j.at("wirelessBand").get<SystemDevices::WirelessBand>());
        x.set_unfiltered_friendly_type(SystemDevices::get_optional<std::string>(j, "unfilteredFriendlyType"));
        x.set_unfiltered_curated_oui_name(SystemDevices::get_optional<std::string>(j, "unfilteredCuratedOuiName"));
        x.set_automatic_friendly_name(j.at("automaticFriendlyName").get<std::string>());
        x.set_curated_oui_name(SystemDevices::get_optional<std::string>(j, "curatedOuiName"));
        x.set_ip_addresses(SystemDevices::get_optional<std::vector<std::string>>(j, "ipAddresses"));
        x.set_connected(SystemDevices::get_optional<bool>(j, "connected"));
        x.set_ip_address(SystemDevices::get_optional<std::string>(j, "ipAddress"));
        x.set_station_type(SystemDevices::get_optional<std::string>(j, "stationType"));
    }

    inline void to_json(json &j, const SystemDevices::Station &x) {
        j = json::object();
        j["id"] = x.get_id();
        j["friendlyName"] = x.get_friendly_name();
        j["friendlyType"] = x.get_friendly_type();
        j["connectionType"] = x.get_connection_type();
        j["apId"] = x.get_ap_id();
        j["wirelessBand"] = x.get_wireless_band();
        j["unfilteredFriendlyType"] = x.get_unfiltered_friendly_type();
        j["unfilteredCuratedOuiName"] = x.get_unfiltered_curated_oui_name();
        j["automaticFriendlyName"] = x.get_automatic_friendly_name();
        j["curatedOuiName"] = x.get_curated_oui_name();
        j["ipAddresses"] = x.get_ip_addresses();
        j["connected"] = x.get_connected();
        j["ipAddress"] = x.get_ip_address();
        j["stationType"] = x.get_station_type();
    }

    inline void from_json(const json &j, SystemDevices::Welcome &x) {
        x.set_stations(j.at("stations").get<std::vector<SystemDevices::Station>>());
    }

    inline void to_json(json &j, const SystemDevices::Welcome &x) {
        j = json::object();
        j["stations"] = x.get_stations();
    }

    inline void from_json(const json &j, SystemDevices::ConnectionType &x) {
        if (j == "WIRED") x = SystemDevices::ConnectionType::WIRED;
        else if (j == "WIRELESS") x = SystemDevices::ConnectionType::WIRELESS;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json &j, const SystemDevices::ConnectionType &x) {
        switch (x) {
            case SystemDevices::ConnectionType::WIRED:
                j = "WIRED";
                break;
            case SystemDevices::ConnectionType::WIRELESS:
                j = "WIRELESS";
                break;
            default:
                throw "This should not happen";
        }
    }

    inline void from_json(const json &j, SystemDevices::WirelessBand &x) {
        if (j == "BAND_2400_MHZ") x = SystemDevices::WirelessBand::BAND_2400__MHZ;
        else if (j == "BAND_5000_MHZ") x = SystemDevices::WirelessBand::BAND_5000__MHZ;
        else if (j == "NOT_APPLICABLE") x = SystemDevices::WirelessBand::NOT_APPLICABLE;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json &j, const SystemDevices::WirelessBand &x) {
        switch (x) {
            case SystemDevices::WirelessBand::BAND_2400__MHZ:
                j = "BAND_2400_MHZ";
                break;
            case SystemDevices::WirelessBand::BAND_5000__MHZ:
                j = "BAND_5000_MHZ";
                break;
            case SystemDevices::WirelessBand::NOT_APPLICABLE:
                j = "NOT_APPLICABLE";
                break;
            default:
                throw "This should not happen";
        }
    }
}
