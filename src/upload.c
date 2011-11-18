#include <stdio.h> 
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <mxml.h>
#include <sys/stat.h>
#include <fcntl.h>



struct MemoryStruct {
  char *memory;
    size_t size;
	};

static size_t response_data(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if (mem->memory == NULL) {
		     /* out of memory! */ 
     printf("not enough memory (realloc returned NULL)\n");
     exit(EXIT_FAILURE);
   }
					    
   memcpy(&(mem->memory[mem->size]), contents, realsize);
   mem->size += realsize;
   mem->memory[mem->size] = 0;
  return realsize;

}







int main(int argc, char *argv[]){
 CURL *handle;
 CURLcode result;
 struct curl_httppost *post=NULL;
 struct curl_httppost *lastptr=NULL;
 FILE *fd;
 mxml_node_t *tree;
 mxml_node_t *node;
struct MemoryStruct chunk;
 
   chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */ 
     chunk.size = 0; 

   printf("START \n");
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
	  





    curl_easy_setopt(handle, CURLOPT_URL,"http://api.imgur.com/2/upload");
   // curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, response_data);
 
 
    curl_easy_setopt(handle, CURLOPT_HTTPPOST, post);
//    curl_easy_setopt(handle, CURLOPT_WRITEDATA, fd);
	  
	
  
  result = curl_easy_perform(handle);
  
printf("debug2");
   tree = mxmlLoadFile(NULL, fd,
                        MXML_TEXT_CALLBACK);
 printf("debug3");
   node = mxmlFindElement(tree, tree, "links",
		                           "href", NULL,
								                              MXML_DESCEND);

printf("debug4");
printf("url is %s\n", node->value.text.string);

curl_formfree(post);
   }   
 return 0;
}

