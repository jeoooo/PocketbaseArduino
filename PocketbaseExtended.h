// PocketbaseExtended.h repo test

#ifndef PocketbaseExtended_h
#define PocketbaseExtended_h

#include "Arduino.h"

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <BearSSLHelpers.h>

class PocketbaseExtended
{
public:
    PocketbaseExtended(const char *baseUrl); // Constructor

    // Methods to build collection and record URLs
    PocketbaseExtended &collection(const char *collection);

    /**
     * @brief           Fetches a single record from a Pocketbase collection
     *
     * @param recordId  The ID of the record to view.
     *
     * @param expand    (Optional) Auto expand record relations. Ex.:?expand=relField1,relField2.subRelField Supports up to 6-levels depth nested relations expansion.
     *                  The expanded relations will be appended to the record under the expand property (eg. "expand": {"relField1": {...}, ...}).
     *                  Only the relations to which the request user has permissions to view will be expanded.
     *
     * @param fields    (Optional) Comma separated string of the fields to return in the JSON response (by default returns all fields). Ex.: ?fields=*,expand.relField.name
     *                  * targets all keys from the specific depth level.
     *                  In addition, the following field modifiers are also supported:
     *                  :excerpt(maxLength, withEllipsis?)
     *                  Returns a short plain text version of the field string value.
     *                  Ex.: ?fields=*,description:excerpt(200,true)
     *
     *                  For more information, see: https://pocketbase.io/docs
     */
    String getOne(
        const char *recordId,
        const char *expand /* = nullptr */,
        const char *fields /* = nullptr */);

    /**
     * @brief           Deletes a single record from a Pocketbase collection
     *
     * @param recordId  The ID of the record to delete.
     *
     *                  For more information, see: https://pocketbase.io/docs
     */
    String deleteRecord(const char *recordId);

    /**
     * @brief           Fetches a multiple records from a Pocketbase collection. Supports sorting and filtering.
     *
     * @param page      The page (aka. offset) of the paginated list (default to 1).
     *
     * @param perPage   Specify the max returned records per page (default to 30).
     *
     * @param sort      Specify the records order attribute(s).
     *                  Add - / + (default) in front of the attribute for DESC / ASC order. Ex.:
     *                  `DESC by created and ASC by id`
     *                  `?sort=-created,id`
     *
     * @param filter    Filter the returned records.
     *
     * @param expand    (Optional) Auto expand record relations. Ex.:?expand=relField1,relField2.subRelField Supports up to 6-levels depth nested relations expansion.
     *                  The expanded relations will be appended to the record under the expand property (eg. "expand": {"relField1": {...}, ...}).
     *                  Only the relations to which the request user has permissions to view will be expanded.
     *
     * @param fields    (Optional) Comma separated string of the fields to return in the JSON response (by default returns all fields). Ex.: ?fields=*,expand.relField.name
     *                  * targets all keys from the specific depth level.
     *                  In addition, the following field modifiers are also supported:
     *                  :excerpt(maxLength, withEllipsis?)
     *                  Returns a short plain text version of the field string value.
     *                  Ex.: ?fields=*,description:excerpt(200,true)
     *
     * @param skipTotal If it is set the total counts query will be skipped and the response fields totalItems and totalPages will have -1 value.
     *                  This could drastically speed up the search queries when the total counters are not needed or cursor based pagination is used.
     *                  For optimization purposes, it is set by default for the getFirstListItem() and getFullList() SDKs methods.
     *
     *                  For more information, see: https://pocketbase.io/docs
     */
    String getList(
        const char *page /* = nullptr */,
        const char *perPage /* = nullptr */,
        const char *sort /* = nullptr */,
        const char *filter /* = nullptr */,
        const char *skipTotal /* = nullptr */,
        const char *expand /* = nullptr */,
        const char *fields /* = nullptr */);

    String create(const String &requestBody);

private:
    String base_url;
    String current_endpoint;
    String expand_param;
    String fields_param;
};

#endif
