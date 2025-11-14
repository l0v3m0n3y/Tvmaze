#ifndef TVMAZE_H
#define TVMAZE_H

#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <pplx/pplx.h>
#include <iostream>
#include <string>
#include <map>

using namespace web;
using namespace web::http;
using namespace web::http::client;

class Tvmaze {
private:
    std::string api_base = "https://api.tvmaze.com";
    http_client_config client_config;
    
    http_request create_request(const std::string& path, method m) {
        http_request request(m);
        
        // Полный набор браузерных заголовков
        request.headers().add("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
        request.headers().add("User-Agent", "Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/115.0");
        
        request.set_request_uri(utility::conversions::to_string_t(path));
        return request;
    }

public:
    Tvmaze() {
        client_config.set_validate_certificates(false);
    }

    pplx::task<json::value> get_show(int shows_id,const std::string& embed ="") {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        
        std::string path = "/shows/" + std::to_string(shows_id);
        bool first_param = true;
        if (!embed.empty()) {
           path += (first_param ? "?" : "&") + std::string("embed=") + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(embed)));
           first_param = false;}
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }
    pplx::task<json::value> search_people(const std::string& people) {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        
        std::string path = "/search/people?q=" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(people)));
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }
    pplx::task<json::value> get_schedule(const std::string& country="",const std::string& date="") {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/schedule";
        bool first_param = true;
        if (!country.empty()) {
           path += (first_param ? "?" : "&") + std::string("country=") + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(country)));
           first_param = false;}
        if (!date.empty()) {
            path += (first_param ? "?" : "&") + std::string("date=") + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(date)));
            first_param = false;
        }
    
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }
    pplx::task<json::value> get_web_schedule(const std::string& country="",const std::string& date="") {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/schedule/web";
        bool first_param = true;
        if (!country.empty()) {
           path += (first_param ? "?" : "&") + std::string("country=") + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(country)));
           first_param = false;}
        if (!date.empty()) {
            path += (first_param ? "?" : "&") + std::string("date=") + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(date)));
            first_param = false;
        }
    
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }
    pplx::task<json::value> get_updates(const std::string& type="shows",const std::string& since="") {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/updates/" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(type)));
        bool first_param = true;
        if (!since.empty()) {
           path += (first_param ? "?" : "&") + std::string("since=") + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(since)));
           first_param = false;}
    
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }
    pplx::task<json::value> get_show_episodes(int show_id,int specials=0) {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/shows/"+ std::to_string(show_id) + "/episodes";
        bool first_param = true;
        if (specials!=0) {
           path += (first_param ? "?" : "&") + std::string("specials=") + std::to_string(specials);
           first_param = false;}
    
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }
    pplx::task<json::value> get_show_list(int page=1) {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/shows";
        bool first_param = true;
        if (page!=1) {
           path += (first_param ? "?" : "&") + std::string("page=") + std::to_string(page);
           first_param = false;}
    
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }
    pplx::task<json::value> get_people_list(int page=1) {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/people";
        bool first_param = true;
        if (page!=1) {
           path += (first_param ? "?" : "&") + std::string("page=") + std::to_string(page);
           first_param = false;}
    
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }
    pplx::task<json::value> get_show_alternatelists(int show_id,const std::string& embed ="") {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/alternatelists/" + std::to_string(show_id) + "/alternateepisodes";
        bool first_param = true;
        if (!embed.empty()) {
           path += (first_param ? "?" : "&") + std::string("embed=") + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(embed)));
           first_param = false;}
    
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }
    pplx::task<json::value> single_search(const std::string& q ="",const std::string& embed ="") {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "singlesearch/shows";
        bool first_param = true;
        if (!q.empty()) {
           path += (first_param ? "?" : "&") + std::string("q=") + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(q)));
           first_param = false;}
        if (!embed.empty()) {
           path += (first_param ? "?" : "&") + std::string("embed=") + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(embed)));
           first_param = false;}
    
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }
    pplx::task<json::value> episodes_list(int episode_id ,const std::string& embed ="") {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/episodes/" + std::to_string(episode_id);
        bool first_param = true;
        if (!embed.empty()) {
           path += (first_param ? "?" : "&") + std::string("embed=") + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(embed)));
           first_param = false;}
    
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }
    pplx::task<json::value> episodes_guestcast_list(int episode_id) {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/episodes/" + std::to_string(episode_id) + "/guestcast";
        bool first_param = true;
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }
    pplx::task<json::value> episodes_guestcrew_list(int episode_id) {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/episodes/" + std::to_string(episode_id) + "/guestcrew";
    
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }

    pplx::task<json::value> get_people(int people_id ,const std::string& embed ="") {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/people/" + std::to_string(people_id);
        bool first_param = true;
        if (!embed.empty()) {
           path += (first_param ? "?" : "&") + std::string("embed=") + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(embed)));
           first_param = false;}
    
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }

    pplx::task<json::value> get_people_castcredits(int people_id ,const std::string& embed ="") {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/people/" + std::to_string(people_id) + "/castcredits";
        bool first_param = true;
        if (!embed.empty()) {
           path += (first_param ? "?" : "&") + std::string("embed=") + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(embed)));
           first_param = false;}
    
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }

    pplx::task<json::value> get_people_guestcastcredits(int people_id ,const std::string& embed ="") {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/people/" + std::to_string(people_id) + "/guestcastcredits";
        bool first_param = true;
        if (!embed.empty()) {
           path += (first_param ? "?" : "&") + std::string("embed=") + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(embed)));
           first_param = false;}
    
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }

    pplx::task<json::value> get_seasons_episodes(int seasons_id ,const std::string& embed ="") {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/seasons/" + std::to_string(seasons_id) + "/episodes";
        bool first_param = true;
        if (!embed.empty()) {
           path += (first_param ? "?" : "&") + std::string("embed=") + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(embed)));
           first_param = false;}
    
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }

    pplx::task<json::value> get_episode_by_number(int shows_id ,int season, int number) {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/shows/" + std::to_string(shows_id) + "/episodebynumber?season=" + std::to_string(season) + "number=" + std::to_string(season);
    
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }

    pplx::task<json::value> get_episode_by_date(int shows_id ,const std::string& date) {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/shows/" + std::to_string(shows_id) + "/episodesbydate?date=" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(date)));
    
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }

    pplx::task<json::value> get_show_seasons(int shows_id) {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/shows/" + std::to_string(shows_id) + "/seasons";
    
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }

    pplx::task<json::value> get_show_cast(int shows_id) {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/shows/" + std::to_string(shows_id) + "/cast";
    
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }

    pplx::task<json::value> get_show_crew(int shows_id) {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/shows/" + std::to_string(shows_id) + "/crew";
    
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }

    pplx::task<json::value> get_show_akas(int shows_id) {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/shows/" + std::to_string(shows_id) + "/akas";
    
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }

    pplx::task<json::value> get_show_images(int shows_id) {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/shows/" + std::to_string(shows_id) + "/images";
    
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }
};

#endif
