#include <stdio.h> 
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <jansson.h>

#define BUFFER_SIZE  (256 * 1024)  /* 256 KB */


struct write_result
{
    char *data;
	    int pos;
		};


static size_t write_response(void *ptr, size_t size, size_t nmemb, void *stream)
{
    struct write_result *result = (struct write_result *)stream;

	    if(result->pos + size * nmemb >= BUFFER_SIZE - 1)
		    {
			        fprintf(stderr, "error: too small buffer\n");
					        return 0;
							    }

								    memcpy(result->data + result->pos, ptr, size * nmemb);
									    result->pos += size * nmemb;

										    return size * nmemb;
											}






int main(int argc, char *argv[]){
 CURL *handle;
 CURLcode result;
 struct curl_httppost *post=NULL;
 struct curl_httppost *lastptr=NULL;
 char *data;

data = malloc(BUFFER_SIZE);
struct write_result write_result = {
				        .data = data,
						        .pos = 0
								    };



 unsigned int i;
     char *text;
		     json_t *root;
			     json_error_t error;
				     json_t *links;


   handle = curl_easy_init();






   if (handle){

   /* Fill in the file upload field */ 
     curl_formadd(&post,
	              &lastptr,
					CURLFORM_COPYNAME, "key",
					CURLFORM_COPYCONTENTS,"0426cb779599180503fd02a0e134ff03",
					CURLFORM_END);
																  
     curl_formadd(&post,
	              &lastptr,
	                      CURLFORM_COPYNAME, "image",
	                      CURLFORM_FILE, "test.png",
	                      CURLFORM_END);
	  





    curl_easy_setopt(handle, CURLOPT_URL,"http://api.imgur.com/2/upload.json");
   curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_response);
 
   curl_easy_setopt(handle, CURLOPT_WRITEDATA, &write_result); 
   curl_easy_setopt(handle, CURLOPT_HTTPPOST, post);
	  
	
  
  result = curl_easy_perform(handle);
  
    curl_formfree(post);
    curl_easy_cleanup(handle);
    curl_global_cleanup();

		    data[write_result.pos] = '\0';
    
    text = data;
	root = json_loads(text ,0, &error);
	    free(text);



		    if(!root)
			    {
				        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
						        return 1;
								    }



json_t *original, *date, *name;
const char *message_text;
if(!json_object_get(root, "upload")){
printf("nope\n");}


original = json_object_get(root, "upload");


original = json_object_get(original, "links");
 
 original = json_object_get(original, "original");
         if(!json_is_string(original))
		         {
				             fprintf(stderr, "error: commit %d: message is not a string\n", i + 1);
							             return 1;
										         }

											         message_text = json_string_value(original);
											
														         printf("%s\n",
																							                  message_text);

   }   
 return 0;
}

