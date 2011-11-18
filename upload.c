#include <curl/curl.h>
#include <string.h>
#include <keys.h>

struct curl_httppost *post=NULL;  
struct curl_httppost *last=NULL;

void main() {
easyhandle = curl_easy_init();
 curl_formadd(&post, &last,   CURLFORM_COPYNAME, "image",   CURLFORM_FILECONTENT, "test.png", CURLFORM_END);
curl_formadd(&post, &last,   CURLFORM_COPYNAME, "key",   CURLFORM_FILECONTENT, key, CURLFORM_END);

curl_easy_setopt(easyhandle, CURLOPT_POSTFIELDS, data);
curl_easy_setopt(easyhandle, CURLOPT_URL, "http:////api.imgur.com/2/upload.xml")
curl_easy_perform(easyhandle);

curl_formfree(post);
}

