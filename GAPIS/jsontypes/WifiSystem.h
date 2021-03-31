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
    template <typename T>
    struct adl_serializer<std::shared_ptr<T>> {
        static void to_json(json & j, const std::shared_ptr<T> & opt) {
            if (!opt) j = nullptr; else j = *opt;
        }

        static std::shared_ptr<T> from_json(const json & j) {
            if (j.is_null()) return std::unique_ptr<T>(); else return std::unique_ptr<T>(new T(j.get<T>()));
        }
    };
}
#endif

namespace WifiSystem {
    using nlohmann::json;

    inline json get_untyped(const json & j, const char * property) {
        if (j.find(property) != j.end()) {
            return j.at(property).get<json>();
        }
        return json();
    }

    inline json get_untyped(const json & j, std::string property) {
        return get_untyped(j, property.data());
    }

    template <typename T>
    inline std::shared_ptr<T> get_optional(const json & j, const char * property) {
        if (j.find(property) != j.end()) {
            return j.at(property).get<std::shared_ptr<T>>();
        }
        return std::shared_ptr<T>();
    }

    template <typename T>
    inline std::shared_ptr<T> get_optional(const json & j, std::string property) {
        return get_optional<T>(j, property.data());
    }

    class GlobalSettings {
    public:
        GlobalSettings() = default;
        virtual ~GlobalSettings() = default;

    private:
        std::string gwael_phase;

    public:
        const std::string & get_gwael_phase() const { return gwael_phase; }
        std::string & get_mutable_gwael_phase() { return gwael_phase; }
        void set_gwael_phase(const std::string & value) { this->gwael_phase = value; }
    };

    class JoinMeshResult {
    public:
        JoinMeshResult() = default;
        virtual ~JoinMeshResult() = default;

    private:
        std::string result;

    public:
        const std::string & get_result() const { return result; }
        std::string & get_mutable_result() { return result; }
        void set_result(const std::string & value) { this->result = value; }
    };

    class AccessPointProperties {
    public:
        AccessPointProperties() = default;
        virtual ~AccessPointProperties() = default;

    private:
        std::string ip_address;
        std::string last_seen_time;
        std::string firmware_version;
        std::string oem_name;
        std::string hardware_type;
        std::shared_ptr<bool> is_bridged;
        bool setup_completed;
        std::string hybrid_device_state;
        std::string operating_mode;
        JoinMeshResult join_mesh_result;
        std::string serial_number;
        std::shared_ptr<bool> is_group_root;

    public:
        const std::string & get_ip_address() const { return ip_address; }
        std::string & get_mutable_ip_address() { return ip_address; }
        void set_ip_address(const std::string & value) { this->ip_address = value; }

        const std::string & get_last_seen_time() const { return last_seen_time; }
        std::string & get_mutable_last_seen_time() { return last_seen_time; }
        void set_last_seen_time(const std::string & value) { this->last_seen_time = value; }

        const std::string & get_firmware_version() const { return firmware_version; }
        std::string & get_mutable_firmware_version() { return firmware_version; }
        void set_firmware_version(const std::string & value) { this->firmware_version = value; }

        const std::string & get_oem_name() const { return oem_name; }
        std::string & get_mutable_oem_name() { return oem_name; }
        void set_oem_name(const std::string & value) { this->oem_name = value; }

        const std::string & get_hardware_type() const { return hardware_type; }
        std::string & get_mutable_hardware_type() { return hardware_type; }
        void set_hardware_type(const std::string & value) { this->hardware_type = value; }

        std::shared_ptr<bool> get_is_bridged() const { return is_bridged; }
        void set_is_bridged(std::shared_ptr<bool> value) { this->is_bridged = value; }

        const bool & get_setup_completed() const { return setup_completed; }
        bool & get_mutable_setup_completed() { return setup_completed; }
        void set_setup_completed(const bool & value) { this->setup_completed = value; }

        const std::string & get_hybrid_device_state() const { return hybrid_device_state; }
        std::string & get_mutable_hybrid_device_state() { return hybrid_device_state; }
        void set_hybrid_device_state(const std::string & value) { this->hybrid_device_state = value; }

        const std::string & get_operating_mode() const { return operating_mode; }
        std::string & get_mutable_operating_mode() { return operating_mode; }
        void set_operating_mode(const std::string & value) { this->operating_mode = value; }

        const JoinMeshResult & get_join_mesh_result() const { return join_mesh_result; }
        JoinMeshResult & get_mutable_join_mesh_result() { return join_mesh_result; }
        void set_join_mesh_result(const JoinMeshResult & value) { this->join_mesh_result = value; }

        const std::string & get_serial_number() const { return serial_number; }
        std::string & get_mutable_serial_number() { return serial_number; }
        void set_serial_number(const std::string & value) { this->serial_number = value; }

        std::shared_ptr<bool> get_is_group_root() const { return is_group_root; }
        void set_is_group_root(std::shared_ptr<bool> value) { this->is_group_root = value; }
    };

    class ApplicationPrioritizationProperties {
    public:
        ApplicationPrioritizationProperties() = default;
        virtual ~ApplicationPrioritizationProperties() = default;

    private:

    public:
    };

    class AccessPointOtherSettings {
    public:
        AccessPointOtherSettings() = default;
        virtual ~AccessPointOtherSettings() = default;

    private:
        std::string ap_name;
        ApplicationPrioritizationProperties room_data;
        std::string isp_type;

    public:
        const std::string & get_ap_name() const { return ap_name; }
        std::string & get_mutable_ap_name() { return ap_name; }
        void set_ap_name(const std::string & value) { this->ap_name = value; }

        const ApplicationPrioritizationProperties & get_room_data() const { return room_data; }
        ApplicationPrioritizationProperties & get_mutable_room_data() { return room_data; }
        void set_room_data(const ApplicationPrioritizationProperties & value) { this->room_data = value; }

        const std::string & get_isp_type() const { return isp_type; }
        std::string & get_mutable_isp_type() { return isp_type; }
        void set_isp_type(const std::string & value) { this->isp_type = value; }
    };

    class LightingSettings {
    public:
        LightingSettings() = default;
        virtual ~LightingSettings() = default;

    private:
        int64_t intensity;
        bool light_off_when_muted;

    public:
        const int64_t & get_intensity() const { return intensity; }
        int64_t & get_mutable_intensity() { return intensity; }
        void set_intensity(const int64_t & value) { this->intensity = value; }

        const bool & get_light_off_when_muted() const { return light_off_when_muted; }
        bool & get_mutable_light_off_when_muted() { return light_off_when_muted; }
        void set_light_off_when_muted(const bool & value) { this->light_off_when_muted = value; }
    };

    class AccessPointSettings {
    public:
        AccessPointSettings() = default;
        virtual ~AccessPointSettings() = default;

    private:
        LightingSettings lighting_settings;
        AccessPointOtherSettings access_point_other_settings;

    public:
        const LightingSettings & get_lighting_settings() const { return lighting_settings; }
        LightingSettings & get_mutable_lighting_settings() { return lighting_settings; }
        void set_lighting_settings(const LightingSettings & value) { this->lighting_settings = value; }

        const AccessPointOtherSettings & get_access_point_other_settings() const { return access_point_other_settings; }
        AccessPointOtherSettings & get_mutable_access_point_other_settings() { return access_point_other_settings; }
        void set_access_point_other_settings(const AccessPointOtherSettings & value) { this->access_point_other_settings = value; }
    };

    class AccessPoint {
    public:
        AccessPoint() = default;
        virtual ~AccessPoint() = default;

    private:
        std::string id;
        AccessPointSettings access_point_settings;
        AccessPointProperties access_point_properties;

    public:
        const std::string & get_id() const { return id; }
        std::string & get_mutable_id() { return id; }
        void set_id(const std::string & value) { this->id = value; }

        const AccessPointSettings & get_access_point_settings() const { return access_point_settings; }
        AccessPointSettings & get_mutable_access_point_settings() { return access_point_settings; }
        void set_access_point_settings(const AccessPointSettings & value) { this->access_point_settings = value; }

        const AccessPointProperties & get_access_point_properties() const { return access_point_properties; }
        AccessPointProperties & get_mutable_access_point_properties() { return access_point_properties; }
        void set_access_point_properties(const AccessPointProperties & value) { this->access_point_properties = value; }
    };

    class LanProperties {
    public:
        LanProperties() = default;
        virtual ~LanProperties() = default;

    private:
        std::string ip_netmask;

    public:
        const std::string & get_ip_netmask() const { return ip_netmask; }
        std::string & get_mutable_ip_netmask() { return ip_netmask; }
        void set_ip_netmask(const std::string & value) { this->ip_netmask = value; }
    };

    enum class SupportStatus : int { SUPPORTED };

    class DhcpIpReservation {
    public:
        DhcpIpReservation() = default;
        virtual ~DhcpIpReservation() = default;

    private:
        SupportStatus support_status;

    public:
        const SupportStatus & get_support_status() const { return support_status; }
        SupportStatus & get_mutable_support_status() { return support_status; }
        void set_support_status(const SupportStatus & value) { this->support_status = value; }
    };

    class Capabilities {
    public:
        Capabilities() = default;
        virtual ~Capabilities() = default;

    private:
        DhcpIpReservation home_app_migration;
        DhcpIpReservation wpa3;
        DhcpIpReservation gaming_preferred_qos;
        DhcpIpReservation video_conferencing_preferred_qos;
        DhcpIpReservation historical_network_data;
        DhcpIpReservation station_list;
        DhcpIpReservation family_wifi;
        DhcpIpReservation guest_network_shared_devices;
        DhcpIpReservation port_management;
        DhcpIpReservation dhcp_ip_reservation;

    public:
        const DhcpIpReservation & get_home_app_migration() const { return home_app_migration; }
        DhcpIpReservation & get_mutable_home_app_migration() { return home_app_migration; }
        void set_home_app_migration(const DhcpIpReservation & value) { this->home_app_migration = value; }

        const DhcpIpReservation & get_wpa3() const { return wpa3; }
        DhcpIpReservation & get_mutable_wpa3() { return wpa3; }
        void set_wpa3(const DhcpIpReservation & value) { this->wpa3 = value; }

        const DhcpIpReservation & get_gaming_preferred_qos() const { return gaming_preferred_qos; }
        DhcpIpReservation & get_mutable_gaming_preferred_qos() { return gaming_preferred_qos; }
        void set_gaming_preferred_qos(const DhcpIpReservation & value) { this->gaming_preferred_qos = value; }

        const DhcpIpReservation & get_video_conferencing_preferred_qos() const { return video_conferencing_preferred_qos; }
        DhcpIpReservation & get_mutable_video_conferencing_preferred_qos() { return video_conferencing_preferred_qos; }
        void set_video_conferencing_preferred_qos(const DhcpIpReservation & value) { this->video_conferencing_preferred_qos = value; }

        const DhcpIpReservation & get_historical_network_data() const { return historical_network_data; }
        DhcpIpReservation & get_mutable_historical_network_data() { return historical_network_data; }
        void set_historical_network_data(const DhcpIpReservation & value) { this->historical_network_data = value; }

        const DhcpIpReservation & get_station_list() const { return station_list; }
        DhcpIpReservation & get_mutable_station_list() { return station_list; }
        void set_station_list(const DhcpIpReservation & value) { this->station_list = value; }

        const DhcpIpReservation & get_family_wifi() const { return family_wifi; }
        DhcpIpReservation & get_mutable_family_wifi() { return family_wifi; }
        void set_family_wifi(const DhcpIpReservation & value) { this->family_wifi = value; }

        const DhcpIpReservation & get_guest_network_shared_devices() const { return guest_network_shared_devices; }
        DhcpIpReservation & get_mutable_guest_network_shared_devices() { return guest_network_shared_devices; }
        void set_guest_network_shared_devices(const DhcpIpReservation & value) { this->guest_network_shared_devices = value; }

        const DhcpIpReservation & get_port_management() const { return port_management; }
        DhcpIpReservation & get_mutable_port_management() { return port_management; }
        void set_port_management(const DhcpIpReservation & value) { this->port_management = value; }

        const DhcpIpReservation & get_dhcp_ip_reservation() const { return dhcp_ip_reservation; }
        DhcpIpReservation & get_mutable_dhcp_ip_reservation() { return dhcp_ip_reservation; }
        void set_dhcp_ip_reservation(const DhcpIpReservation & value) { this->dhcp_ip_reservation = value; }
    };

    class OtherProperties {
    public:
        OtherProperties() = default;
        virtual ~OtherProperties() = default;

    private:
        std::string firmware_version;
        std::string encouraged_update;
        std::string family_premium_expiry;
        std::string synchronous_update_estimated_time_remaining;
        Capabilities capabilities;

    public:
        const std::string & get_firmware_version() const { return firmware_version; }
        std::string & get_mutable_firmware_version() { return firmware_version; }
        void set_firmware_version(const std::string & value) { this->firmware_version = value; }

        const std::string & get_encouraged_update() const { return encouraged_update; }
        std::string & get_mutable_encouraged_update() { return encouraged_update; }
        void set_encouraged_update(const std::string & value) { this->encouraged_update = value; }

        const std::string & get_family_premium_expiry() const { return family_premium_expiry; }
        std::string & get_mutable_family_premium_expiry() { return family_premium_expiry; }
        void set_family_premium_expiry(const std::string & value) { this->family_premium_expiry = value; }

        const std::string & get_synchronous_update_estimated_time_remaining() const { return synchronous_update_estimated_time_remaining; }
        std::string & get_mutable_synchronous_update_estimated_time_remaining() { return synchronous_update_estimated_time_remaining; }
        void set_synchronous_update_estimated_time_remaining(const std::string & value) { this->synchronous_update_estimated_time_remaining = value; }

        const Capabilities & get_capabilities() const { return capabilities; }
        Capabilities & get_mutable_capabilities() { return capabilities; }
        void set_capabilities(const Capabilities & value) { this->capabilities = value; }
    };

    class Ipv6Properties {
    public:
        Ipv6Properties() = default;
        virtual ~Ipv6Properties() = default;

    private:
        std::string status;

    public:
        const std::string & get_status() const { return status; }
        std::string & get_mutable_status() { return status; }
        void set_status(const std::string & value) { this->status = value; }
    };

    class WanProperties {
    public:
        WanProperties() = default;
        virtual ~WanProperties() = default;

    private:
        std::string wan_mode;
        std::string ip_address;
        std::string gateway;
        std::vector<std::string> dns_servers;
        Ipv6Properties ipv6_properties;
        std::vector<std::string> wan_dns_servers;

    public:
        const std::string & get_wan_mode() const { return wan_mode; }
        std::string & get_mutable_wan_mode() { return wan_mode; }
        void set_wan_mode(const std::string & value) { this->wan_mode = value; }

        const std::string & get_ip_address() const { return ip_address; }
        std::string & get_mutable_ip_address() { return ip_address; }
        void set_ip_address(const std::string & value) { this->ip_address = value; }

        const std::string & get_gateway() const { return gateway; }
        std::string & get_mutable_gateway() { return gateway; }
        void set_gateway(const std::string & value) { this->gateway = value; }

        const std::vector<std::string> & get_dns_servers() const { return dns_servers; }
        std::vector<std::string> & get_mutable_dns_servers() { return dns_servers; }
        void set_dns_servers(const std::vector<std::string> & value) { this->dns_servers = value; }

        const Ipv6Properties & get_ipv6_properties() const { return ipv6_properties; }
        Ipv6Properties & get_mutable_ipv6_properties() { return ipv6_properties; }
        void set_ipv6_properties(const Ipv6Properties & value) { this->ipv6_properties = value; }

        const std::vector<std::string> & get_wan_dns_servers() const { return wan_dns_servers; }
        std::vector<std::string> & get_mutable_wan_dns_servers() { return wan_dns_servers; }
        void set_wan_dns_servers(const std::vector<std::string> & value) { this->wan_dns_servers = value; }
    };

    class GroupProperties {
    public:
        GroupProperties() = default;
        virtual ~GroupProperties() = default;

    private:
        WanProperties wan_properties;
        LanProperties lan_properties;
        OtherProperties other_properties;
        ApplicationPrioritizationProperties stadia_prioritization_properties;
        ApplicationPrioritizationProperties application_prioritization_properties;

    public:
        const WanProperties & get_wan_properties() const { return wan_properties; }
        WanProperties & get_mutable_wan_properties() { return wan_properties; }
        void set_wan_properties(const WanProperties & value) { this->wan_properties = value; }

        const LanProperties & get_lan_properties() const { return lan_properties; }
        LanProperties & get_mutable_lan_properties() { return lan_properties; }
        void set_lan_properties(const LanProperties & value) { this->lan_properties = value; }

        const OtherProperties & get_other_properties() const { return other_properties; }
        OtherProperties & get_mutable_other_properties() { return other_properties; }
        void set_other_properties(const OtherProperties & value) { this->other_properties = value; }

        const ApplicationPrioritizationProperties & get_stadia_prioritization_properties() const { return stadia_prioritization_properties; }
        ApplicationPrioritizationProperties & get_mutable_stadia_prioritization_properties() { return stadia_prioritization_properties; }
        void set_stadia_prioritization_properties(const ApplicationPrioritizationProperties & value) { this->stadia_prioritization_properties = value; }

        const ApplicationPrioritizationProperties & get_application_prioritization_properties() const { return application_prioritization_properties; }
        ApplicationPrioritizationProperties & get_mutable_application_prioritization_properties() { return application_prioritization_properties; }
        void set_application_prioritization_properties(const ApplicationPrioritizationProperties & value) { this->application_prioritization_properties = value; }
    };

    class ApplicationPrioritizationSettings {
    public:
        ApplicationPrioritizationSettings() = default;
        virtual ~ApplicationPrioritizationSettings() = default;

    private:
        bool gaming_prioritization_enabled;
        bool video_conferencing_prioritization_enabled;

    public:
        const bool & get_gaming_prioritization_enabled() const { return gaming_prioritization_enabled; }
        bool & get_mutable_gaming_prioritization_enabled() { return gaming_prioritization_enabled; }
        void set_gaming_prioritization_enabled(const bool & value) { this->gaming_prioritization_enabled = value; }

        const bool & get_video_conferencing_prioritization_enabled() const { return video_conferencing_prioritization_enabled; }
        bool & get_mutable_video_conferencing_prioritization_enabled() { return video_conferencing_prioritization_enabled; }
        void set_video_conferencing_prioritization_enabled(const bool & value) { this->video_conferencing_prioritization_enabled = value; }
    };

    class ContentFilteringPolicy {
    public:
        ContentFilteringPolicy() = default;
        virtual ~ContentFilteringPolicy() = default;

    private:
        std::string id;
        std::vector<std::string> station_set_ids;
        std::string safe_filtering_mode;

    public:
        const std::string & get_id() const { return id; }
        std::string & get_mutable_id() { return id; }
        void set_id(const std::string & value) { this->id = value; }

        const std::vector<std::string> & get_station_set_ids() const { return station_set_ids; }
        std::vector<std::string> & get_mutable_station_set_ids() { return station_set_ids; }
        void set_station_set_ids(const std::vector<std::string> & value) { this->station_set_ids = value; }

        const std::string & get_safe_filtering_mode() const { return safe_filtering_mode; }
        std::string & get_mutable_safe_filtering_mode() { return safe_filtering_mode; }
        void set_safe_filtering_mode(const std::string & value) { this->safe_filtering_mode = value; }
    };

    class BlockingPolicy {
    public:
        BlockingPolicy() = default;
        virtual ~BlockingPolicy() = default;

    private:
        std::string creation_timestamp;
        std::string expiry_timestamp;

    public:
        const std::string & get_creation_timestamp() const { return creation_timestamp; }
        std::string & get_mutable_creation_timestamp() { return creation_timestamp; }
        void set_creation_timestamp(const std::string & value) { this->creation_timestamp = value; }

        const std::string & get_expiry_timestamp() const { return expiry_timestamp; }
        std::string & get_mutable_expiry_timestamp() { return expiry_timestamp; }
        void set_expiry_timestamp(const std::string & value) { this->expiry_timestamp = value; }
    };

    class StationPolicy {
    public:
        StationPolicy() = default;
        virtual ~StationPolicy() = default;

    private:
        std::string station_id;
        BlockingPolicy blocking_policy;

    public:
        const std::string & get_station_id() const { return station_id; }
        std::string & get_mutable_station_id() { return station_id; }
        void set_station_id(const std::string & value) { this->station_id = value; }

        const BlockingPolicy & get_blocking_policy() const { return blocking_policy; }
        BlockingPolicy & get_mutable_blocking_policy() { return blocking_policy; }
        void set_blocking_policy(const BlockingPolicy & value) { this->blocking_policy = value; }
    };

    class StationSetPolicy {
    public:
        StationSetPolicy() = default;
        virtual ~StationSetPolicy() = default;

    private:
        std::string station_set_id;
        BlockingPolicy blocking_policy;

    public:
        const std::string & get_station_set_id() const { return station_set_id; }
        std::string & get_mutable_station_set_id() { return station_set_id; }
        void set_station_set_id(const std::string & value) { this->station_set_id = value; }

        const BlockingPolicy & get_blocking_policy() const { return blocking_policy; }
        BlockingPolicy & get_mutable_blocking_policy() { return blocking_policy; }
        void set_blocking_policy(const BlockingPolicy & value) { this->blocking_policy = value; }
    };

    class FamilyHubSettings {
    public:
        FamilyHubSettings() = default;
        virtual ~FamilyHubSettings() = default;

    private:
        std::vector<StationSetPolicy> station_set_policies;
        std::vector<StationPolicy> station_policies;
        std::vector<ContentFilteringPolicy> content_filtering_policies;

    public:
        const std::vector<StationSetPolicy> & get_station_set_policies() const { return station_set_policies; }
        std::vector<StationSetPolicy> & get_mutable_station_set_policies() { return station_set_policies; }
        void set_station_set_policies(const std::vector<StationSetPolicy> & value) { this->station_set_policies = value; }

        const std::vector<StationPolicy> & get_station_policies() const { return station_policies; }
        std::vector<StationPolicy> & get_mutable_station_policies() { return station_policies; }
        void set_station_policies(const std::vector<StationPolicy> & value) { this->station_policies = value; }

        const std::vector<ContentFilteringPolicy> & get_content_filtering_policies() const { return content_filtering_policies; }
        std::vector<ContentFilteringPolicy> & get_mutable_content_filtering_policies() { return content_filtering_policies; }
        void set_content_filtering_policies(const std::vector<ContentFilteringPolicy> & value) { this->content_filtering_policies = value; }
    };

    class GuestWirelessSettings {
    public:
        GuestWirelessSettings() = default;
        virtual ~GuestWirelessSettings() = default;

    private:
        bool enabled;
        std::string ssid;
        bool welcome_mat_enabled;
        bool psk_visible;

    public:
        const bool & get_enabled() const { return enabled; }
        bool & get_mutable_enabled() { return enabled; }
        void set_enabled(const bool & value) { this->enabled = value; }

        const std::string & get_ssid() const { return ssid; }
        std::string & get_mutable_ssid() { return ssid; }
        void set_ssid(const std::string & value) { this->ssid = value; }

        const bool & get_welcome_mat_enabled() const { return welcome_mat_enabled; }
        bool & get_mutable_welcome_mat_enabled() { return welcome_mat_enabled; }
        void set_welcome_mat_enabled(const bool & value) { this->welcome_mat_enabled = value; }

        const bool & get_psk_visible() const { return psk_visible; }
        bool & get_mutable_psk_visible() { return psk_visible; }
        void set_psk_visible(const bool & value) { this->psk_visible = value; }
    };

    class DefaultPrioritizedStation {
    public:
        DefaultPrioritizedStation() = default;
        virtual ~DefaultPrioritizedStation() = default;

    private:
        std::string prioritization_duration;

    public:
        const std::string & get_prioritization_duration() const { return prioritization_duration; }
        std::string & get_mutable_prioritization_duration() { return prioritization_duration; }
        void set_prioritization_duration(const std::string & value) { this->prioritization_duration = value; }
    };

    class PrioritizedStation {
    public:
        PrioritizedStation() = default;
        virtual ~PrioritizedStation() = default;

    private:
        std::string prioritization_end_time;
        std::string station_id;

    public:
        const std::string & get_prioritization_end_time() const { return prioritization_end_time; }
        std::string & get_mutable_prioritization_end_time() { return prioritization_end_time; }
        void set_prioritization_end_time(const std::string & value) { this->prioritization_end_time = value; }

        const std::string & get_station_id() const { return station_id; }
        std::string & get_mutable_station_id() { return station_id; }
        void set_station_id(const std::string & value) { this->station_id = value; }
    };

    class StaticIpMapping {
    public:
        StaticIpMapping() = default;
        virtual ~StaticIpMapping() = default;

    private:
        std::string station_id;
        std::string ip_address;

    public:
        const std::string & get_station_id() const { return station_id; }
        std::string & get_mutable_station_id() { return station_id; }
        void set_station_id(const std::string & value) { this->station_id = value; }

        const std::string & get_ip_address() const { return ip_address; }
        std::string & get_mutable_ip_address() { return ip_address; }
        void set_ip_address(const std::string & value) { this->ip_address = value; }
    };

    class LanSettings {
    public:
        LanSettings() = default;
        virtual ~LanSettings() = default;

    private:
        bool upnp_enabled;
        std::vector<StaticIpMapping> static_ip_mappings;
        PrioritizedStation prioritized_station;
        DefaultPrioritizedStation default_prioritized_station;
        std::string ip_address;
        std::string netmask;
        std::string dhcp_pool_begin;
        std::string dhcp_pool_end;

    public:
        const bool & get_upnp_enabled() const { return upnp_enabled; }
        bool & get_mutable_upnp_enabled() { return upnp_enabled; }
        void set_upnp_enabled(const bool & value) { this->upnp_enabled = value; }

        const std::vector<StaticIpMapping> & get_static_ip_mappings() const { return static_ip_mappings; }
        std::vector<StaticIpMapping> & get_mutable_static_ip_mappings() { return static_ip_mappings; }
        void set_static_ip_mappings(const std::vector<StaticIpMapping> & value) { this->static_ip_mappings = value; }

        const PrioritizedStation & get_prioritized_station() const { return prioritized_station; }
        PrioritizedStation & get_mutable_prioritized_station() { return prioritized_station; }
        void set_prioritized_station(const PrioritizedStation & value) { this->prioritized_station = value; }

        const DefaultPrioritizedStation & get_default_prioritized_station() const { return default_prioritized_station; }
        DefaultPrioritizedStation & get_mutable_default_prioritized_station() { return default_prioritized_station; }
        void set_default_prioritized_station(const DefaultPrioritizedStation & value) { this->default_prioritized_station = value; }

        const std::string & get_ip_address() const { return ip_address; }
        std::string & get_mutable_ip_address() { return ip_address; }
        void set_ip_address(const std::string & value) { this->ip_address = value; }

        const std::string & get_netmask() const { return netmask; }
        std::string & get_mutable_netmask() { return netmask; }
        void set_netmask(const std::string & value) { this->netmask = value; }

        const std::string & get_dhcp_pool_begin() const { return dhcp_pool_begin; }
        std::string & get_mutable_dhcp_pool_begin() { return dhcp_pool_begin; }
        void set_dhcp_pool_begin(const std::string & value) { this->dhcp_pool_begin = value; }

        const std::string & get_dhcp_pool_end() const { return dhcp_pool_end; }
        std::string & get_mutable_dhcp_pool_end() { return dhcp_pool_end; }
        void set_dhcp_pool_end(const std::string & value) { this->dhcp_pool_end = value; }
    };

    class MeshSettings {
    public:
        MeshSettings() = default;
        virtual ~MeshSettings() = default;

    private:
        std::string kek;
        std::string mac;

    public:
        const std::string & get_kek() const { return kek; }
        std::string & get_mutable_kek() { return kek; }
        void set_kek(const std::string & value) { this->kek = value; }

        const std::string & get_mac() const { return mac; }
        std::string & get_mutable_mac() { return mac; }
        void set_mac(const std::string & value) { this->mac = value; }
    };

    class Settings {
    public:
        Settings() = default;
        virtual ~Settings() = default;

    private:
        bool enabled;

    public:
        const bool & get_enabled() const { return enabled; }
        bool & get_mutable_enabled() { return enabled; }
        void set_enabled(const bool & value) { this->enabled = value; }
    };

    class DataCollectionSettings {
    public:
        DataCollectionSettings() = default;
        virtual ~DataCollectionSettings() = default;

    private:
        bool anonymous_stats_opt_in;
        bool background_data_collection_opt_in;

    public:
        const bool & get_anonymous_stats_opt_in() const { return anonymous_stats_opt_in; }
        bool & get_mutable_anonymous_stats_opt_in() { return anonymous_stats_opt_in; }
        void set_anonymous_stats_opt_in(const bool & value) { this->anonymous_stats_opt_in = value; }

        const bool & get_background_data_collection_opt_in() const { return background_data_collection_opt_in; }
        bool & get_mutable_background_data_collection_opt_in() { return background_data_collection_opt_in; }
        void set_background_data_collection_opt_in(const bool & value) { this->background_data_collection_opt_in = value; }
    };

    class OtherSettings {
    public:
        OtherSettings() = default;
        virtual ~OtherSettings() = default;

    private:
        std::string update_channel;
        DataCollectionSettings data_collection_settings;

    public:
        const std::string & get_update_channel() const { return update_channel; }
        std::string & get_mutable_update_channel() { return update_channel; }
        void set_update_channel(const std::string & value) { this->update_channel = value; }

        const DataCollectionSettings & get_data_collection_settings() const { return data_collection_settings; }
        DataCollectionSettings & get_mutable_data_collection_settings() { return data_collection_settings; }
        void set_data_collection_settings(const DataCollectionSettings & value) { this->data_collection_settings = value; }
    };

    class Color {
    public:
        Color() = default;
        virtual ~Color() = default;

    private:
        double red;
        double green;
        double blue;

    public:
        const double & get_red() const { return red; }
        double & get_mutable_red() { return red; }
        void set_red(const double & value) { this->red = value; }

        const double & get_green() const { return green; }
        double & get_mutable_green() { return green; }
        void set_green(const double & value) { this->green = value; }

        const double & get_blue() const { return blue; }
        double & get_mutable_blue() { return blue; }
        void set_blue(const double & value) { this->blue = value; }
    };

    class Member {
    public:
        Member() = default;
        virtual ~Member() = default;

    private:
        std::string station_id;

    public:
        const std::string & get_station_id() const { return station_id; }
        std::string & get_mutable_station_id() { return station_id; }
        void set_station_id(const std::string & value) { this->station_id = value; }
    };

    class StationSet {
    public:
        StationSet() = default;
        virtual ~StationSet() = default;

    private:
        std::string id;
        std::string name;
        std::vector<Member> members;
        Color color;

    public:
        const std::string & get_id() const { return id; }
        std::string & get_mutable_id() { return id; }
        void set_id(const std::string & value) { this->id = value; }

        const std::string & get_name() const { return name; }
        std::string & get_mutable_name() { return name; }
        void set_name(const std::string & value) { this->name = value; }

        const std::vector<Member> & get_members() const { return members; }
        std::vector<Member> & get_mutable_members() { return members; }
        void set_members(const std::vector<Member> & value) { this->members = value; }

        const Color & get_color() const { return color; }
        Color & get_mutable_color() { return color; }
        void set_color(const Color & value) { this->color = value; }
    };

    class DnsConfig {
    public:
        DnsConfig() = default;
        virtual ~DnsConfig() = default;

    private:
        std::string dns_mode;

    public:
        const std::string & get_dns_mode() const { return dns_mode; }
        std::string & get_mutable_dns_mode() { return dns_mode; }
        void set_dns_mode(const std::string & value) { this->dns_mode = value; }
    };

    class WanSettings {
    public:
        WanSettings() = default;
        virtual ~WanSettings() = default;

    private:
        bool ipv6_enabled;
        DnsConfig dns_config;

    public:
        const bool & get_ipv6_enabled() const { return ipv6_enabled; }
        bool & get_mutable_ipv6_enabled() { return ipv6_enabled; }
        void set_ipv6_enabled(const bool & value) { this->ipv6_enabled = value; }

        const DnsConfig & get_dns_config() const { return dns_config; }
        DnsConfig & get_mutable_dns_config() { return dns_config; }
        void set_dns_config(const DnsConfig & value) { this->dns_config = value; }
    };

    class WlanSettings {
    public:
        WlanSettings() = default;
        virtual ~WlanSettings() = default;

    private:
        std::string private_ssid;

    public:
        const std::string & get_private_ssid() const { return private_ssid; }
        std::string & get_mutable_private_ssid() { return private_ssid; }
        void set_private_ssid(const std::string & value) { this->private_ssid = value; }
    };

    class GroupSettings {
    public:
        GroupSettings() = default;
        virtual ~GroupSettings() = default;

    private:
        LanSettings lan_settings;
        WlanSettings wlan_settings;
        GuestWirelessSettings guest_wireless_settings;
        WanSettings wan_settings;
        OtherSettings other_settings;
        MeshSettings mesh_settings;
        Settings on_here_settings;
        ApplicationPrioritizationProperties home_control_settings;
        ApplicationPrioritizationProperties cloud_action_settings;
        FamilyHubSettings family_hub_settings;
        std::vector<StationSet> station_sets;
        ApplicationPrioritizationProperties public_wireless_settings;
        Settings stadia_prioritization_settings;
        ApplicationPrioritizationProperties wpa3_settings;
        ApplicationPrioritizationSettings application_prioritization_settings;

    public:
        const LanSettings & get_lan_settings() const { return lan_settings; }
        LanSettings & get_mutable_lan_settings() { return lan_settings; }
        void set_lan_settings(const LanSettings & value) { this->lan_settings = value; }

        const WlanSettings & get_wlan_settings() const { return wlan_settings; }
        WlanSettings & get_mutable_wlan_settings() { return wlan_settings; }
        void set_wlan_settings(const WlanSettings & value) { this->wlan_settings = value; }

        const GuestWirelessSettings & get_guest_wireless_settings() const { return guest_wireless_settings; }
        GuestWirelessSettings & get_mutable_guest_wireless_settings() { return guest_wireless_settings; }
        void set_guest_wireless_settings(const GuestWirelessSettings & value) { this->guest_wireless_settings = value; }

        const WanSettings & get_wan_settings() const { return wan_settings; }
        WanSettings & get_mutable_wan_settings() { return wan_settings; }
        void set_wan_settings(const WanSettings & value) { this->wan_settings = value; }

        const OtherSettings & get_other_settings() const { return other_settings; }
        OtherSettings & get_mutable_other_settings() { return other_settings; }
        void set_other_settings(const OtherSettings & value) { this->other_settings = value; }

        const MeshSettings & get_mesh_settings() const { return mesh_settings; }
        MeshSettings & get_mutable_mesh_settings() { return mesh_settings; }
        void set_mesh_settings(const MeshSettings & value) { this->mesh_settings = value; }

        const Settings & get_on_here_settings() const { return on_here_settings; }
        Settings & get_mutable_on_here_settings() { return on_here_settings; }
        void set_on_here_settings(const Settings & value) { this->on_here_settings = value; }

        const ApplicationPrioritizationProperties & get_home_control_settings() const { return home_control_settings; }
        ApplicationPrioritizationProperties & get_mutable_home_control_settings() { return home_control_settings; }
        void set_home_control_settings(const ApplicationPrioritizationProperties & value) { this->home_control_settings = value; }

        const ApplicationPrioritizationProperties & get_cloud_action_settings() const { return cloud_action_settings; }
        ApplicationPrioritizationProperties & get_mutable_cloud_action_settings() { return cloud_action_settings; }
        void set_cloud_action_settings(const ApplicationPrioritizationProperties & value) { this->cloud_action_settings = value; }

        const FamilyHubSettings & get_family_hub_settings() const { return family_hub_settings; }
        FamilyHubSettings & get_mutable_family_hub_settings() { return family_hub_settings; }
        void set_family_hub_settings(const FamilyHubSettings & value) { this->family_hub_settings = value; }

        const std::vector<StationSet> & get_station_sets() const { return station_sets; }
        std::vector<StationSet> & get_mutable_station_sets() { return station_sets; }
        void set_station_sets(const std::vector<StationSet> & value) { this->station_sets = value; }

        const ApplicationPrioritizationProperties & get_public_wireless_settings() const { return public_wireless_settings; }
        ApplicationPrioritizationProperties & get_mutable_public_wireless_settings() { return public_wireless_settings; }
        void set_public_wireless_settings(const ApplicationPrioritizationProperties & value) { this->public_wireless_settings = value; }

        const Settings & get_stadia_prioritization_settings() const { return stadia_prioritization_settings; }
        Settings & get_mutable_stadia_prioritization_settings() { return stadia_prioritization_settings; }
        void set_stadia_prioritization_settings(const Settings & value) { this->stadia_prioritization_settings = value; }

        const ApplicationPrioritizationProperties & get_wpa3_settings() const { return wpa3_settings; }
        ApplicationPrioritizationProperties & get_mutable_wpa3_settings() { return wpa3_settings; }
        void set_wpa3_settings(const ApplicationPrioritizationProperties & value) { this->wpa3_settings = value; }

        const ApplicationPrioritizationSettings & get_application_prioritization_settings() const { return application_prioritization_settings; }
        ApplicationPrioritizationSettings & get_mutable_application_prioritization_settings() { return application_prioritization_settings; }
        void set_application_prioritization_settings(const ApplicationPrioritizationSettings & value) { this->application_prioritization_settings = value; }
    };

    class Manager {
    public:
        Manager() = default;
        virtual ~Manager() = default;

    private:
        std::string manager_id;
        std::string email_address;
        bool is_owner;

    public:
        const std::string & get_manager_id() const { return manager_id; }
        std::string & get_mutable_manager_id() { return manager_id; }
        void set_manager_id(const std::string & value) { this->manager_id = value; }

        const std::string & get_email_address() const { return email_address; }
        std::string & get_mutable_email_address() { return email_address; }
        void set_email_address(const std::string & value) { this->email_address = value; }

        const bool & get_is_owner() const { return is_owner; }
        bool & get_mutable_is_owner() { return is_owner; }
        void set_is_owner(const bool & value) { this->is_owner = value; }
    };

    class Group {
    public:
        Group() = default;
        virtual ~Group() = default;

    private:
        std::string id;
        std::vector<AccessPoint> access_points;
        GroupSettings group_settings;
        GroupProperties group_properties;
        std::vector<Manager> managers;
        std::string hgs_structure_id;

    public:
        const std::string & get_id() const { return id; }
        std::string & get_mutable_id() { return id; }
        void set_id(const std::string & value) { this->id = value; }

        const std::vector<AccessPoint> & get_access_points() const { return access_points; }
        std::vector<AccessPoint> & get_mutable_access_points() { return access_points; }
        void set_access_points(const std::vector<AccessPoint> & value) { this->access_points = value; }

        const GroupSettings & get_group_settings() const { return group_settings; }
        GroupSettings & get_mutable_group_settings() { return group_settings; }
        void set_group_settings(const GroupSettings & value) { this->group_settings = value; }

        const GroupProperties & get_group_properties() const { return group_properties; }
        GroupProperties & get_mutable_group_properties() { return group_properties; }
        void set_group_properties(const GroupProperties & value) { this->group_properties = value; }

        const std::vector<Manager> & get_managers() const { return managers; }
        std::vector<Manager> & get_mutable_managers() { return managers; }
        void set_managers(const std::vector<Manager> & value) { this->managers = value; }

        const std::string & get_hgs_structure_id() const { return hgs_structure_id; }
        std::string & get_mutable_hgs_structure_id() { return hgs_structure_id; }
        void set_hgs_structure_id(const std::string & value) { this->hgs_structure_id = value; }
    };

    class Welcome {
    public:
        Welcome() = default;
        virtual ~Welcome() = default;

    private:
        std::vector<Group> groups;
        GlobalSettings global_settings;

    public:
        const std::vector<Group> & get_groups() const { return groups; }
        std::vector<Group> & get_mutable_groups() { return groups; }
        void set_groups(const std::vector<Group> & value) { this->groups = value; }

        const GlobalSettings & get_global_settings() const { return global_settings; }
        GlobalSettings & get_mutable_global_settings() { return global_settings; }
        void set_global_settings(const GlobalSettings & value) { this->global_settings = value; }
    };
}

namespace nlohmann {
    void from_json(const json & j, WifiSystem::GlobalSettings & x);
    void to_json(json & j, const WifiSystem::GlobalSettings & x);

    void from_json(const json & j, WifiSystem::JoinMeshResult & x);
    void to_json(json & j, const WifiSystem::JoinMeshResult & x);

    void from_json(const json & j, WifiSystem::AccessPointProperties & x);
    void to_json(json & j, const WifiSystem::AccessPointProperties & x);

    void from_json(const json & j, WifiSystem::ApplicationPrioritizationProperties & x);
    void to_json(json & j, const WifiSystem::ApplicationPrioritizationProperties & x);

    void from_json(const json & j, WifiSystem::AccessPointOtherSettings & x);
    void to_json(json & j, const WifiSystem::AccessPointOtherSettings & x);

    void from_json(const json & j, WifiSystem::LightingSettings & x);
    void to_json(json & j, const WifiSystem::LightingSettings & x);

    void from_json(const json & j, WifiSystem::AccessPointSettings & x);
    void to_json(json & j, const WifiSystem::AccessPointSettings & x);

    void from_json(const json & j, WifiSystem::AccessPoint & x);
    void to_json(json & j, const WifiSystem::AccessPoint & x);

    void from_json(const json & j, WifiSystem::LanProperties & x);
    void to_json(json & j, const WifiSystem::LanProperties & x);

    void from_json(const json & j, WifiSystem::DhcpIpReservation & x);
    void to_json(json & j, const WifiSystem::DhcpIpReservation & x);

    void from_json(const json & j, WifiSystem::Capabilities & x);
    void to_json(json & j, const WifiSystem::Capabilities & x);

    void from_json(const json & j, WifiSystem::OtherProperties & x);
    void to_json(json & j, const WifiSystem::OtherProperties & x);

    void from_json(const json & j, WifiSystem::Ipv6Properties & x);
    void to_json(json & j, const WifiSystem::Ipv6Properties & x);

    void from_json(const json & j, WifiSystem::WanProperties & x);
    void to_json(json & j, const WifiSystem::WanProperties & x);

    void from_json(const json & j, WifiSystem::GroupProperties & x);
    void to_json(json & j, const WifiSystem::GroupProperties & x);

    void from_json(const json & j, WifiSystem::ApplicationPrioritizationSettings & x);
    void to_json(json & j, const WifiSystem::ApplicationPrioritizationSettings & x);

    void from_json(const json & j, WifiSystem::ContentFilteringPolicy & x);
    void to_json(json & j, const WifiSystem::ContentFilteringPolicy & x);

    void from_json(const json & j, WifiSystem::BlockingPolicy & x);
    void to_json(json & j, const WifiSystem::BlockingPolicy & x);

    void from_json(const json & j, WifiSystem::StationPolicy & x);
    void to_json(json & j, const WifiSystem::StationPolicy & x);

    void from_json(const json & j, WifiSystem::StationSetPolicy & x);
    void to_json(json & j, const WifiSystem::StationSetPolicy & x);

    void from_json(const json & j, WifiSystem::FamilyHubSettings & x);
    void to_json(json & j, const WifiSystem::FamilyHubSettings & x);

    void from_json(const json & j, WifiSystem::GuestWirelessSettings & x);
    void to_json(json & j, const WifiSystem::GuestWirelessSettings & x);

    void from_json(const json & j, WifiSystem::DefaultPrioritizedStation & x);
    void to_json(json & j, const WifiSystem::DefaultPrioritizedStation & x);

    void from_json(const json & j, WifiSystem::PrioritizedStation & x);
    void to_json(json & j, const WifiSystem::PrioritizedStation & x);

    void from_json(const json & j, WifiSystem::StaticIpMapping & x);
    void to_json(json & j, const WifiSystem::StaticIpMapping & x);

    void from_json(const json & j, WifiSystem::LanSettings & x);
    void to_json(json & j, const WifiSystem::LanSettings & x);

    void from_json(const json & j, WifiSystem::MeshSettings & x);
    void to_json(json & j, const WifiSystem::MeshSettings & x);

    void from_json(const json & j, WifiSystem::Settings & x);
    void to_json(json & j, const WifiSystem::Settings & x);

    void from_json(const json & j, WifiSystem::DataCollectionSettings & x);
    void to_json(json & j, const WifiSystem::DataCollectionSettings & x);

    void from_json(const json & j, WifiSystem::OtherSettings & x);
    void to_json(json & j, const WifiSystem::OtherSettings & x);

    void from_json(const json & j, WifiSystem::Color & x);
    void to_json(json & j, const WifiSystem::Color & x);

    void from_json(const json & j, WifiSystem::Member & x);
    void to_json(json & j, const WifiSystem::Member & x);

    void from_json(const json & j, WifiSystem::StationSet & x);
    void to_json(json & j, const WifiSystem::StationSet & x);

    void from_json(const json & j, WifiSystem::DnsConfig & x);
    void to_json(json & j, const WifiSystem::DnsConfig & x);

    void from_json(const json & j, WifiSystem::WanSettings & x);
    void to_json(json & j, const WifiSystem::WanSettings & x);

    void from_json(const json & j, WifiSystem::WlanSettings & x);
    void to_json(json & j, const WifiSystem::WlanSettings & x);

    void from_json(const json & j, WifiSystem::GroupSettings & x);
    void to_json(json & j, const WifiSystem::GroupSettings & x);

    void from_json(const json & j, WifiSystem::Manager & x);
    void to_json(json & j, const WifiSystem::Manager & x);

    void from_json(const json & j, WifiSystem::Group & x);
    void to_json(json & j, const WifiSystem::Group & x);

    void from_json(const json & j, WifiSystem::Welcome & x);
    void to_json(json & j, const WifiSystem::Welcome & x);

    void from_json(const json & j, WifiSystem::SupportStatus & x);
    void to_json(json & j, const WifiSystem::SupportStatus & x);

    inline void from_json(const json & j, WifiSystem::GlobalSettings& x) {
        x.set_gwael_phase(j.at("gwaelPhase").get<std::string>());
    }

    inline void to_json(json & j, const WifiSystem::GlobalSettings & x) {
        j = json::object();
        j["gwaelPhase"] = x.get_gwael_phase();
    }

    inline void from_json(const json & j, WifiSystem::JoinMeshResult& x) {
        x.set_result(j.at("result").get<std::string>());
    }

    inline void to_json(json & j, const WifiSystem::JoinMeshResult & x) {
        j = json::object();
        j["result"] = x.get_result();
    }

    inline void from_json(const json & j, WifiSystem::AccessPointProperties& x) {
        x.set_ip_address(j.at("ipAddress").get<std::string>());
        x.set_last_seen_time(j.at("lastSeenTime").get<std::string>());
        x.set_firmware_version(j.at("firmwareVersion").get<std::string>());
        x.set_oem_name(j.at("oemName").get<std::string>());
        x.set_hardware_type(j.at("hardwareType").get<std::string>());
        x.set_is_bridged(WifiSystem::get_optional<bool>(j, "isBridged"));
        x.set_setup_completed(j.at("setupCompleted").get<bool>());
        x.set_hybrid_device_state(j.at("hybridDeviceState").get<std::string>());
        x.set_operating_mode(j.at("operatingMode").get<std::string>());
        x.set_join_mesh_result(j.at("joinMeshResult").get<WifiSystem::JoinMeshResult>());
        x.set_serial_number(j.at("serialNumber").get<std::string>());
        x.set_is_group_root(WifiSystem::get_optional<bool>(j, "isGroupRoot"));
    }

    inline void to_json(json & j, const WifiSystem::AccessPointProperties & x) {
        j = json::object();
        j["ipAddress"] = x.get_ip_address();
        j["lastSeenTime"] = x.get_last_seen_time();
        j["firmwareVersion"] = x.get_firmware_version();
        j["oemName"] = x.get_oem_name();
        j["hardwareType"] = x.get_hardware_type();
        j["isBridged"] = x.get_is_bridged();
        j["setupCompleted"] = x.get_setup_completed();
        j["hybridDeviceState"] = x.get_hybrid_device_state();
        j["operatingMode"] = x.get_operating_mode();
        j["joinMeshResult"] = x.get_join_mesh_result();
        j["serialNumber"] = x.get_serial_number();
        j["isGroupRoot"] = x.get_is_group_root();
    }

    inline void from_json(const json & j, WifiSystem::ApplicationPrioritizationProperties& x) {
    }

    inline void to_json(json & j, const WifiSystem::ApplicationPrioritizationProperties & x) {
        j = json::object();
    }

    inline void from_json(const json & j, WifiSystem::AccessPointOtherSettings& x) {
        x.set_ap_name(j.at("apName").get<std::string>());
        x.set_room_data(j.at("roomData").get<WifiSystem::ApplicationPrioritizationProperties>());
        x.set_isp_type(j.at("ispType").get<std::string>());
    }

    inline void to_json(json & j, const WifiSystem::AccessPointOtherSettings & x) {
        j = json::object();
        j["apName"] = x.get_ap_name();
        j["roomData"] = x.get_room_data();
        j["ispType"] = x.get_isp_type();
    }

    inline void from_json(const json & j, WifiSystem::LightingSettings& x) {
        x.set_intensity(j.at("intensity").get<int64_t>());
        x.set_light_off_when_muted(j.at("lightOffWhenMuted").get<bool>());
    }

    inline void to_json(json & j, const WifiSystem::LightingSettings & x) {
        j = json::object();
        j["intensity"] = x.get_intensity();
        j["lightOffWhenMuted"] = x.get_light_off_when_muted();
    }

    inline void from_json(const json & j, WifiSystem::AccessPointSettings& x) {
        x.set_lighting_settings(j.at("lightingSettings").get<WifiSystem::LightingSettings>());
        x.set_access_point_other_settings(j.at("accessPointOtherSettings").get<WifiSystem::AccessPointOtherSettings>());
    }

    inline void to_json(json & j, const WifiSystem::AccessPointSettings & x) {
        j = json::object();
        j["lightingSettings"] = x.get_lighting_settings();
        j["accessPointOtherSettings"] = x.get_access_point_other_settings();
    }

    inline void from_json(const json & j, WifiSystem::AccessPoint& x) {
        x.set_id(j.at("id").get<std::string>());
        x.set_access_point_settings(j.at("accessPointSettings").get<WifiSystem::AccessPointSettings>());
        x.set_access_point_properties(j.at("accessPointProperties").get<WifiSystem::AccessPointProperties>());
    }

    inline void to_json(json & j, const WifiSystem::AccessPoint & x) {
        j = json::object();
        j["id"] = x.get_id();
        j["accessPointSettings"] = x.get_access_point_settings();
        j["accessPointProperties"] = x.get_access_point_properties();
    }

    inline void from_json(const json & j, WifiSystem::LanProperties& x) {
        x.set_ip_netmask(j.at("ipNetmask").get<std::string>());
    }

    inline void to_json(json & j, const WifiSystem::LanProperties & x) {
        j = json::object();
        j["ipNetmask"] = x.get_ip_netmask();
    }

    inline void from_json(const json & j, WifiSystem::DhcpIpReservation& x) {
        x.set_support_status(j.at("supportStatus").get<WifiSystem::SupportStatus>());
    }

    inline void to_json(json & j, const WifiSystem::DhcpIpReservation & x) {
        j = json::object();
        j["supportStatus"] = x.get_support_status();
    }

    inline void from_json(const json & j, WifiSystem::Capabilities& x) {
        x.set_home_app_migration(j.at("homeAppMigration").get<WifiSystem::DhcpIpReservation>());
        x.set_wpa3(j.at("wpa3").get<WifiSystem::DhcpIpReservation>());
        x.set_gaming_preferred_qos(j.at("gamingPreferredQos").get<WifiSystem::DhcpIpReservation>());
        x.set_video_conferencing_preferred_qos(j.at("videoConferencingPreferredQos").get<WifiSystem::DhcpIpReservation>());
        x.set_historical_network_data(j.at("historicalNetworkData").get<WifiSystem::DhcpIpReservation>());
        x.set_station_list(j.at("stationList").get<WifiSystem::DhcpIpReservation>());
        x.set_family_wifi(j.at("familyWifi").get<WifiSystem::DhcpIpReservation>());
        x.set_guest_network_shared_devices(j.at("guestNetworkSharedDevices").get<WifiSystem::DhcpIpReservation>());
        x.set_port_management(j.at("portManagement").get<WifiSystem::DhcpIpReservation>());
        x.set_dhcp_ip_reservation(j.at("dhcpIpReservation").get<WifiSystem::DhcpIpReservation>());
    }

    inline void to_json(json & j, const WifiSystem::Capabilities & x) {
        j = json::object();
        j["homeAppMigration"] = x.get_home_app_migration();
        j["wpa3"] = x.get_wpa3();
        j["gamingPreferredQos"] = x.get_gaming_preferred_qos();
        j["videoConferencingPreferredQos"] = x.get_video_conferencing_preferred_qos();
        j["historicalNetworkData"] = x.get_historical_network_data();
        j["stationList"] = x.get_station_list();
        j["familyWifi"] = x.get_family_wifi();
        j["guestNetworkSharedDevices"] = x.get_guest_network_shared_devices();
        j["portManagement"] = x.get_port_management();
        j["dhcpIpReservation"] = x.get_dhcp_ip_reservation();
    }

    inline void from_json(const json & j, WifiSystem::OtherProperties& x) {
        x.set_firmware_version(j.at("firmwareVersion").get<std::string>());
        x.set_encouraged_update(j.at("encouragedUpdate").get<std::string>());
        x.set_family_premium_expiry(j.at("familyPremiumExpiry").get<std::string>());
        x.set_synchronous_update_estimated_time_remaining(j.at("synchronousUpdateEstimatedTimeRemaining").get<std::string>());
        x.set_capabilities(j.at("capabilities").get<WifiSystem::Capabilities>());
    }

    inline void to_json(json & j, const WifiSystem::OtherProperties & x) {
        j = json::object();
        j["firmwareVersion"] = x.get_firmware_version();
        j["encouragedUpdate"] = x.get_encouraged_update();
        j["familyPremiumExpiry"] = x.get_family_premium_expiry();
        j["synchronousUpdateEstimatedTimeRemaining"] = x.get_synchronous_update_estimated_time_remaining();
        j["capabilities"] = x.get_capabilities();
    }

    inline void from_json(const json & j, WifiSystem::Ipv6Properties& x) {
        x.set_status(j.at("status").get<std::string>());
    }

    inline void to_json(json & j, const WifiSystem::Ipv6Properties & x) {
        j = json::object();
        j["status"] = x.get_status();
    }

    inline void from_json(const json & j, WifiSystem::WanProperties& x) {
        x.set_wan_mode(j.at("wanMode").get<std::string>());
        x.set_ip_address(j.at("ipAddress").get<std::string>());
        x.set_gateway(j.at("gateway").get<std::string>());
        x.set_dns_servers(j.at("dnsServers").get<std::vector<std::string>>());
        x.set_ipv6_properties(j.at("ipv6Properties").get<WifiSystem::Ipv6Properties>());
        x.set_wan_dns_servers(j.at("wanDnsServers").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const WifiSystem::WanProperties & x) {
        j = json::object();
        j["wanMode"] = x.get_wan_mode();
        j["ipAddress"] = x.get_ip_address();
        j["gateway"] = x.get_gateway();
        j["dnsServers"] = x.get_dns_servers();
        j["ipv6Properties"] = x.get_ipv6_properties();
        j["wanDnsServers"] = x.get_wan_dns_servers();
    }

    inline void from_json(const json & j, WifiSystem::GroupProperties& x) {
        x.set_wan_properties(j.at("wanProperties").get<WifiSystem::WanProperties>());
        x.set_lan_properties(j.at("lanProperties").get<WifiSystem::LanProperties>());
        x.set_other_properties(j.at("otherProperties").get<WifiSystem::OtherProperties>());
        x.set_stadia_prioritization_properties(j.at("stadiaPrioritizationProperties").get<WifiSystem::ApplicationPrioritizationProperties>());
        x.set_application_prioritization_properties(j.at("applicationPrioritizationProperties").get<WifiSystem::ApplicationPrioritizationProperties>());
    }

    inline void to_json(json & j, const WifiSystem::GroupProperties & x) {
        j = json::object();
        j["wanProperties"] = x.get_wan_properties();
        j["lanProperties"] = x.get_lan_properties();
        j["otherProperties"] = x.get_other_properties();
        j["stadiaPrioritizationProperties"] = x.get_stadia_prioritization_properties();
        j["applicationPrioritizationProperties"] = x.get_application_prioritization_properties();
    }

    inline void from_json(const json & j, WifiSystem::ApplicationPrioritizationSettings& x) {
        x.set_gaming_prioritization_enabled(j.at("gamingPrioritizationEnabled").get<bool>());
        x.set_video_conferencing_prioritization_enabled(j.at("videoConferencingPrioritizationEnabled").get<bool>());
    }

    inline void to_json(json & j, const WifiSystem::ApplicationPrioritizationSettings & x) {
        j = json::object();
        j["gamingPrioritizationEnabled"] = x.get_gaming_prioritization_enabled();
        j["videoConferencingPrioritizationEnabled"] = x.get_video_conferencing_prioritization_enabled();
    }

    inline void from_json(const json & j, WifiSystem::ContentFilteringPolicy& x) {
        x.set_id(j.at("id").get<std::string>());
        x.set_station_set_ids(j.at("stationSetIds").get<std::vector<std::string>>());
        x.set_safe_filtering_mode(j.at("safeFilteringMode").get<std::string>());
    }

    inline void to_json(json & j, const WifiSystem::ContentFilteringPolicy & x) {
        j = json::object();
        j["id"] = x.get_id();
        j["stationSetIds"] = x.get_station_set_ids();
        j["safeFilteringMode"] = x.get_safe_filtering_mode();
    }

    inline void from_json(const json & j, WifiSystem::BlockingPolicy& x) {
        x.set_creation_timestamp(j.at("creationTimestamp").get<std::string>());
        x.set_expiry_timestamp(j.at("expiryTimestamp").get<std::string>());
    }

    inline void to_json(json & j, const WifiSystem::BlockingPolicy & x) {
        j = json::object();
        j["creationTimestamp"] = x.get_creation_timestamp();
        j["expiryTimestamp"] = x.get_expiry_timestamp();
    }

    inline void from_json(const json & j, WifiSystem::StationPolicy& x) {
        x.set_station_id(j.at("stationId").get<std::string>());
        x.set_blocking_policy(j.at("blockingPolicy").get<WifiSystem::BlockingPolicy>());
    }

    inline void to_json(json & j, const WifiSystem::StationPolicy & x) {
        j = json::object();
        j["stationId"] = x.get_station_id();
        j["blockingPolicy"] = x.get_blocking_policy();
    }

    inline void from_json(const json & j, WifiSystem::StationSetPolicy& x) {
        x.set_station_set_id(j.at("stationSetId").get<std::string>());
        x.set_blocking_policy(j.at("blockingPolicy").get<WifiSystem::BlockingPolicy>());
    }

    inline void to_json(json & j, const WifiSystem::StationSetPolicy & x) {
        j = json::object();
        j["stationSetId"] = x.get_station_set_id();
        j["blockingPolicy"] = x.get_blocking_policy();
    }

    inline void from_json(const json & j, WifiSystem::FamilyHubSettings& x) {
        x.set_station_set_policies(j.at("stationSetPolicies").get<std::vector<WifiSystem::StationSetPolicy>>());
        x.set_station_policies(j.at("stationPolicies").get<std::vector<WifiSystem::StationPolicy>>());
        x.set_content_filtering_policies(j.at("contentFilteringPolicies").get<std::vector<WifiSystem::ContentFilteringPolicy>>());
    }

    inline void to_json(json & j, const WifiSystem::FamilyHubSettings & x) {
        j = json::object();
        j["stationSetPolicies"] = x.get_station_set_policies();
        j["stationPolicies"] = x.get_station_policies();
        j["contentFilteringPolicies"] = x.get_content_filtering_policies();
    }

    inline void from_json(const json & j, WifiSystem::GuestWirelessSettings& x) {
        x.set_enabled(j.at("enabled").get<bool>());
        x.set_ssid(j.at("ssid").get<std::string>());
        x.set_welcome_mat_enabled(j.at("welcomeMatEnabled").get<bool>());
        x.set_psk_visible(j.at("pskVisible").get<bool>());
    }

    inline void to_json(json & j, const WifiSystem::GuestWirelessSettings & x) {
        j = json::object();
        j["enabled"] = x.get_enabled();
        j["ssid"] = x.get_ssid();
        j["welcomeMatEnabled"] = x.get_welcome_mat_enabled();
        j["pskVisible"] = x.get_psk_visible();
    }

    inline void from_json(const json & j, WifiSystem::DefaultPrioritizedStation& x) {
        x.set_prioritization_duration(j.at("prioritizationDuration").get<std::string>());
    }

    inline void to_json(json & j, const WifiSystem::DefaultPrioritizedStation & x) {
        j = json::object();
        j["prioritizationDuration"] = x.get_prioritization_duration();
    }

    inline void from_json(const json & j, WifiSystem::PrioritizedStation& x) {
        x.set_prioritization_end_time(j.at("prioritizationEndTime").get<std::string>());
        x.set_station_id(j.at("stationId").get<std::string>());
    }

    inline void to_json(json & j, const WifiSystem::PrioritizedStation & x) {
        j = json::object();
        j["prioritizationEndTime"] = x.get_prioritization_end_time();
        j["stationId"] = x.get_station_id();
    }

    inline void from_json(const json & j, WifiSystem::StaticIpMapping& x) {
        x.set_station_id(j.at("stationId").get<std::string>());
        x.set_ip_address(j.at("ipAddress").get<std::string>());
    }

    inline void to_json(json & j, const WifiSystem::StaticIpMapping & x) {
        j = json::object();
        j["stationId"] = x.get_station_id();
        j["ipAddress"] = x.get_ip_address();
    }

    inline void from_json(const json & j, WifiSystem::LanSettings& x) {
        x.set_upnp_enabled(j.at("upnpEnabled").get<bool>());
        x.set_static_ip_mappings(j.at("staticIpMappings").get<std::vector<WifiSystem::StaticIpMapping>>());
        x.set_prioritized_station(j.at("prioritizedStation").get<WifiSystem::PrioritizedStation>());
        x.set_default_prioritized_station(j.at("defaultPrioritizedStation").get<WifiSystem::DefaultPrioritizedStation>());
        x.set_ip_address(j.at("ipAddress").get<std::string>());
        x.set_netmask(j.at("netmask").get<std::string>());
        x.set_dhcp_pool_begin(j.at("dhcpPoolBegin").get<std::string>());
        x.set_dhcp_pool_end(j.at("dhcpPoolEnd").get<std::string>());
    }

    inline void to_json(json & j, const WifiSystem::LanSettings & x) {
        j = json::object();
        j["upnpEnabled"] = x.get_upnp_enabled();
        j["staticIpMappings"] = x.get_static_ip_mappings();
        j["prioritizedStation"] = x.get_prioritized_station();
        j["defaultPrioritizedStation"] = x.get_default_prioritized_station();
        j["ipAddress"] = x.get_ip_address();
        j["netmask"] = x.get_netmask();
        j["dhcpPoolBegin"] = x.get_dhcp_pool_begin();
        j["dhcpPoolEnd"] = x.get_dhcp_pool_end();
    }

    inline void from_json(const json & j, WifiSystem::MeshSettings& x) {
        x.set_kek(j.at("kek").get<std::string>());
        x.set_mac(j.at("mac").get<std::string>());
    }

    inline void to_json(json & j, const WifiSystem::MeshSettings & x) {
        j = json::object();
        j["kek"] = x.get_kek();
        j["mac"] = x.get_mac();
    }

    inline void from_json(const json & j, WifiSystem::Settings& x) {
        x.set_enabled(j.at("enabled").get<bool>());
    }

    inline void to_json(json & j, const WifiSystem::Settings & x) {
        j = json::object();
        j["enabled"] = x.get_enabled();
    }

    inline void from_json(const json & j, WifiSystem::DataCollectionSettings& x) {
        x.set_anonymous_stats_opt_in(j.at("anonymousStatsOptIn").get<bool>());
        x.set_background_data_collection_opt_in(j.at("backgroundDataCollectionOptIn").get<bool>());
    }

    inline void to_json(json & j, const WifiSystem::DataCollectionSettings & x) {
        j = json::object();
        j["anonymousStatsOptIn"] = x.get_anonymous_stats_opt_in();
        j["backgroundDataCollectionOptIn"] = x.get_background_data_collection_opt_in();
    }

    inline void from_json(const json & j, WifiSystem::OtherSettings& x) {
        x.set_update_channel(j.at("updateChannel").get<std::string>());
        x.set_data_collection_settings(j.at("dataCollectionSettings").get<WifiSystem::DataCollectionSettings>());
    }

    inline void to_json(json & j, const WifiSystem::OtherSettings & x) {
        j = json::object();
        j["updateChannel"] = x.get_update_channel();
        j["dataCollectionSettings"] = x.get_data_collection_settings();
    }

    inline void from_json(const json & j, WifiSystem::Color& x) {
        x.set_red(j.at("red").get<double>());
        x.set_green(j.at("green").get<double>());
        x.set_blue(j.at("blue").get<double>());
    }

    inline void to_json(json & j, const WifiSystem::Color & x) {
        j = json::object();
        j["red"] = x.get_red();
        j["green"] = x.get_green();
        j["blue"] = x.get_blue();
    }

    inline void from_json(const json & j, WifiSystem::Member& x) {
        x.set_station_id(j.at("stationId").get<std::string>());
    }

    inline void to_json(json & j, const WifiSystem::Member & x) {
        j = json::object();
        j["stationId"] = x.get_station_id();
    }

    inline void from_json(const json & j, WifiSystem::StationSet& x) {
        x.set_id(j.at("id").get<std::string>());
        x.set_name(j.at("name").get<std::string>());
        x.set_members(j.at("members").get<std::vector<WifiSystem::Member>>());
        x.set_color(j.at("color").get<WifiSystem::Color>());
    }

    inline void to_json(json & j, const WifiSystem::StationSet & x) {
        j = json::object();
        j["id"] = x.get_id();
        j["name"] = x.get_name();
        j["members"] = x.get_members();
        j["color"] = x.get_color();
    }

    inline void from_json(const json & j, WifiSystem::DnsConfig& x) {
        x.set_dns_mode(j.at("dnsMode").get<std::string>());
    }

    inline void to_json(json & j, const WifiSystem::DnsConfig & x) {
        j = json::object();
        j["dnsMode"] = x.get_dns_mode();
    }

    inline void from_json(const json & j, WifiSystem::WanSettings& x) {
        x.set_ipv6_enabled(j.at("ipv6Enabled").get<bool>());
        x.set_dns_config(j.at("dnsConfig").get<WifiSystem::DnsConfig>());
    }

    inline void to_json(json & j, const WifiSystem::WanSettings & x) {
        j = json::object();
        j["ipv6Enabled"] = x.get_ipv6_enabled();
        j["dnsConfig"] = x.get_dns_config();
    }

    inline void from_json(const json & j, WifiSystem::WlanSettings& x) {
        x.set_private_ssid(j.at("privateSsid").get<std::string>());
    }

    inline void to_json(json & j, const WifiSystem::WlanSettings & x) {
        j = json::object();
        j["privateSsid"] = x.get_private_ssid();
    }

    inline void from_json(const json & j, WifiSystem::GroupSettings& x) {
        x.set_lan_settings(j.at("lanSettings").get<WifiSystem::LanSettings>());
        x.set_wlan_settings(j.at("wlanSettings").get<WifiSystem::WlanSettings>());
        x.set_guest_wireless_settings(j.at("guestWirelessSettings").get<WifiSystem::GuestWirelessSettings>());
        x.set_wan_settings(j.at("wanSettings").get<WifiSystem::WanSettings>());
        x.set_other_settings(j.at("otherSettings").get<WifiSystem::OtherSettings>());
        x.set_mesh_settings(j.at("meshSettings").get<WifiSystem::MeshSettings>());
        x.set_on_here_settings(j.at("onHereSettings").get<WifiSystem::Settings>());
        x.set_home_control_settings(j.at("homeControlSettings").get<WifiSystem::ApplicationPrioritizationProperties>());
        x.set_cloud_action_settings(j.at("cloudActionSettings").get<WifiSystem::ApplicationPrioritizationProperties>());
        x.set_family_hub_settings(j.at("familyHubSettings").get<WifiSystem::FamilyHubSettings>());
        x.set_station_sets(j.at("stationSets").get<std::vector<WifiSystem::StationSet>>());
        x.set_public_wireless_settings(j.at("publicWirelessSettings").get<WifiSystem::ApplicationPrioritizationProperties>());
        x.set_stadia_prioritization_settings(j.at("stadiaPrioritizationSettings").get<WifiSystem::Settings>());
        x.set_wpa3_settings(j.at("wpa3Settings").get<WifiSystem::ApplicationPrioritizationProperties>());
        x.set_application_prioritization_settings(j.at("applicationPrioritizationSettings").get<WifiSystem::ApplicationPrioritizationSettings>());
    }

    inline void to_json(json & j, const WifiSystem::GroupSettings & x) {
        j = json::object();
        j["lanSettings"] = x.get_lan_settings();
        j["wlanSettings"] = x.get_wlan_settings();
        j["guestWirelessSettings"] = x.get_guest_wireless_settings();
        j["wanSettings"] = x.get_wan_settings();
        j["otherSettings"] = x.get_other_settings();
        j["meshSettings"] = x.get_mesh_settings();
        j["onHereSettings"] = x.get_on_here_settings();
        j["homeControlSettings"] = x.get_home_control_settings();
        j["cloudActionSettings"] = x.get_cloud_action_settings();
        j["familyHubSettings"] = x.get_family_hub_settings();
        j["stationSets"] = x.get_station_sets();
        j["publicWirelessSettings"] = x.get_public_wireless_settings();
        j["stadiaPrioritizationSettings"] = x.get_stadia_prioritization_settings();
        j["wpa3Settings"] = x.get_wpa3_settings();
        j["applicationPrioritizationSettings"] = x.get_application_prioritization_settings();
    }

    inline void from_json(const json & j, WifiSystem::Manager& x) {
        x.set_manager_id(j.at("managerId").get<std::string>());
        x.set_email_address(j.at("emailAddress").get<std::string>());
        x.set_is_owner(j.at("isOwner").get<bool>());
    }

    inline void to_json(json & j, const WifiSystem::Manager & x) {
        j = json::object();
        j["managerId"] = x.get_manager_id();
        j["emailAddress"] = x.get_email_address();
        j["isOwner"] = x.get_is_owner();
    }

    inline void from_json(const json & j, WifiSystem::Group& x) {
        x.set_id(j.at("id").get<std::string>());
        x.set_access_points(j.at("accessPoints").get<std::vector<WifiSystem::AccessPoint>>());
        x.set_group_settings(j.at("groupSettings").get<WifiSystem::GroupSettings>());
        x.set_group_properties(j.at("groupProperties").get<WifiSystem::GroupProperties>());
        x.set_managers(j.at("managers").get<std::vector<WifiSystem::Manager>>());
        x.set_hgs_structure_id(j.at("hgsStructureId").get<std::string>());
    }

    inline void to_json(json & j, const WifiSystem::Group & x) {
        j = json::object();
        j["id"] = x.get_id();
        j["accessPoints"] = x.get_access_points();
        j["groupSettings"] = x.get_group_settings();
        j["groupProperties"] = x.get_group_properties();
        j["managers"] = x.get_managers();
        j["hgsStructureId"] = x.get_hgs_structure_id();
    }

    inline void from_json(const json & j, WifiSystem::Welcome& x) {
        x.set_groups(j.at("groups").get<std::vector<WifiSystem::Group>>());
        x.set_global_settings(j.at("globalSettings").get<WifiSystem::GlobalSettings>());
    }

    inline void to_json(json & j, const WifiSystem::Welcome & x) {
        j = json::object();
        j["groups"] = x.get_groups();
        j["globalSettings"] = x.get_global_settings();
    }

    inline void from_json(const json & j, WifiSystem::SupportStatus & x) {
        if (j == "SUPPORTED") x = WifiSystem::SupportStatus::SUPPORTED;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const WifiSystem::SupportStatus & x) {
        switch (x) {
            case WifiSystem::SupportStatus::SUPPORTED: j = "SUPPORTED"; break;
            default: throw "This should not happen";
        }
    }
}
