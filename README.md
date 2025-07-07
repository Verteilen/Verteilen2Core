# Verteilen2Core

The core library for the Vertelien 2 HPC

## Data structure

Which store in the include/data and src/data\
Contains serialization details and structure details

Every structure has its own binary format in order to transmit through network

#### Concept

The network package will have 64 bits integer (Enum) at the very front\
To describe what kind of package is this then after that is the content

Every format have version at the front, this is for the backward compatibility\
If we added more data in the future, we want to make sure all version of data can consume 

#### Job

This will get pass through network a lot, because compute node needs this structure information
to actually know what kind of action she needs to do.

The content of the structure is this\
The second part is for the special binary format
* version (3x32 bits integer)
* uuid (36 bytes)
* category (integer length as enum)
* subCategory (integer length as enum)
* script (dynamic string length)
  * size (integer length)
  * content (dynamic size)
* args size (integer length)
* args (dynamic argument array)
  * type (integer length as the data type enum)
  * size (integer length)
  * content (dynamic size)

#### Task

The task store array of job share pointer

The convertion is a bit tricky, because it only stores job uuid,
and after deserialize, it will store uuid in the buffer,
This means it needs another function that talk to database to generate the job data

It should check database has job, if not create one, this kind of logic should implement on cluster side
Not the core library

The content of the structure is this
* version (3x32 bits integer)
* uuid (36 bytes)
* title (64 bytes)
* description (256 bytes)
* type (integer length as enum)
* cronjobKey (64 bytes)
* multiKey (64 bytes)
* jobs size (integer length)
* jobs (dynamic job array)
  * uuid (36 bytes for job uuid)

#### Project

The project store array of task share pointer

The convertion process have same issue as task, it will store to the buffer as well.\
Again the data generate should implement on cluster side

The content of the structure is this
* version (3x32 bits integer)
* uuid (36 bytes)
* title (64 bytes)
* description (256 bytes)
* binder (36 bytes) The dataset placeholder
* task size (integer length)
* tasks (dynamic task array)
  * uuid (36 bytes for job uuid)

Another special things is the project have another serialize method provides.
Which have content of all the tasks and jobs in it, This is a feature that easier for
user transmit the binary data file around

For the whole deserialize, the memory layout will looks like this
* version (3x32 bits integer)
* uuid (36 bytes)
* title (64 bytes)
* description (256 bytes)
* binder (36 bytes) The dataset placeholder
* task size (integer length)
* tasks (dynamic task array)
  * version (3x32 bits integer)
  * uuid (36 bytes)
  * title (64 bytes)
  * description (256 bytes)
  * type (integer length as enum)
  * cronjobKey (64 bytes)
  * multiKey (64 bytes)
  * jobs size (integer length)
  * jobs (dynamic job array)
    * version (3x32 bits integer)
    * uuid (36 bytes)
    * category (integer length as enum)
    * subCategory (integer length as enum)
    * script (dynamic string length)
      * size (integer length)
      * content (dynamic size)
    * args (dynamic argument array)
      * type (integer length as the data type enum)
      * size (integer length)
      * content (dynamic size)

#### Dataset

