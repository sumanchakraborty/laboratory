**Ansible Modules for Dell EMC PowerMax** Product Guide

**1.2**

Notes, cautions, and warnings
=============================

  **NOTE:** A NOTE indicates important information that helps you make
  better use of your product.

**CAUTION: A CAUTION indicates either potential damage to hardware or
loss of data and tells you how to avoid the problem.**

**WARNING: A WARNING indicates a potential for property damage, personal
injury, or death.**

© 2016 - 2020 Dell Inc. or its subsidiaries. All rights reserved. Dell,
EMC, and other trademarks are trademarks of Dell Inc. or its
subsidiaries. Other trademarks may be trademarks of their respective
owners.

  **1**
>
  **Introduction**
>
  This chapter contains the following topics:

**Topics:**

• Product overview

Product overview
================

  The Ansible Modules for Dell EMC PowerMax are used to automate and
  orchestrate the configuration, and deployment of the Dell EMC PowerMax
  arrays. The capabilities of Ansible modules are managing volumes,
  storage groups, ports, port groups, hosts, host groups, masking views,
  snapshots, SRDF pairings and state, gather high level facts about the
  arrays and RDF group configuration. The options available for each
  capability are list, show, create, delete, and modify.
>
  The Ansible modules are called by tasks within the Ansible playbooks.
  The *Idempotency* feature is enabled for all the modules. The
  *Idempotency* feature enables the playbook to be run multiple times
  and hence supports fault tolerance. The modules use Unisphere RESTAPI
  to interface with the PowerMax arrays.

List of Ansible Modules for Dell EMC PowerMax

  The following are the list of modules:

-   Gather facts module

-   Storage group module

-   Volume module

-   Host module

-   Host group module

-   Port module

-   Port group module

-   Masking view module

-   Snapshot module

-   SRDF module

-   RDF Group module

  **Introduction**
>
  **2**
>
  **Configure Ansible**
>
  This chapter contains the following topics:

**Topics:**

-   Software prerequisites

-   Set up the Ansible host

Software prerequisites
======================

  This table provides information about the software prerequisites for
  the Ansible Modules for Dell EMC PowerMax.

Prerequisites

Table 1. Software prerequisites 
-------------------------------

<table>
<thead>
<tr class="header">
<th><strong>Ansible Modules</strong></th>
<th><strong>Unisphere Version</strong></th>
<th><strong>PowerMaxOS</strong></th>
<th><p><strong>Red Hat</strong></p>
<p><strong>Enterprise Linux</strong></p></th>
<th><strong>Python version</strong></th>
<th><strong>Python library version</strong></th>
<th><strong>Ansible</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>v1.0</td>
<td>9.0</td>
<td><p>5978.221.221</p>
<p>5978.444.444</p></td>
<td>7.5</td>
<td>2.7.12</td>
<td>3.0.0.14</td>
<td>2.6 or later</td>
</tr>
<tr class="even">
<td>v1.1</td>
<td><p>9.0</p>
<p>9.1</p></td>
<td><p>5978.221.221</p>
<p>5978.444.444</p></td>
<td>7.5</td>
<td><p>2.7.12</p>
<p>3.5.2</p></td>
<td>3.1.x</td>
<td>2.6 or later</td>
</tr>
<tr class="odd">
<td>v1.2</td>
<td>9.1 and above</td>
<td><p>5978.221.221</p>
<p>5978.444.444</p>
<p>5978.665.665</p></td>
<td><p>7.5</p>
<p>7.6, 7.7, 7.8, and</p>
<p>8.2</p></td>
<td>2.7 or later</td>
<td>9.1.0.0 and above</td>
<td>2.8 or later</td>
</tr>
<tr class="even">
<td>xxxx</td>
<td>xxxxxxxxxxxxx</td>
<td>xxxxxxxxxxxxxxxxxxx
xxxxxxxxxxxxxxxxxxx
xxxxxxxxxxxxxxxxxxx</td>
<td>xxxxxxxxxx
xxxxxxxxxxxxxxxxxxxxxxxxx
xxxxxxxxxx</td>
<td>xxxxxxxxxxxx</td>
<td>xxxxxxxxxxxxxxxxx</td>
<td>xxxxxxxxxxxx</td>
</tr>
</tbody>
</table>

  **NOTE:** Unisphere Version 9.1 is compatible with PowerMax Python
  library version 9.1.x.x. Similarly, Unisphere version above 9.1 only
  works with Python library version greater than 9.1.x.x.

Set up the Ansible host
=======================

  The Ansible server must be configured to write and run Ansible
  playbooks.

**About this task**

  Do the following before you run playbooks on Ansible modules for Dell
  EMC PowerMax:

**Steps**

1.  Install Python library for Unisphere.

  Run the following command to install PyU4V:
>
  sudo apt install python-pip pip install PyU4V
>
  For more information, see [PyU4V
  Documentation](https://pyu4v.readthedocs.io/en/latest/).
>
  **Configure Ansible**

1.  Create the dellemc folder in one of the following folders if it is
    not available:

    -   For Python 2.7
          /usr/lib/python2.7/site-packages/ansible/modules/storage ● For
          Python 3.5
          /usr/lib/python3.5/site-packages/ansible/modules/storage

2.  Create the dell folder in one of the following folders if it is not
    available:

    -   For Python 2.7
          /usr/lib/python2.7/site-packages/ansible/module\_utils/storage
          ● For Python 3.5
          /usr/lib/python3.5/site-packages/ansible/module\_utils/storage

3.  Copy the Ansible modules to the appropriate locations in the virtual
    machine.

a\. Copy *dellemc\_ansible\_powermax\_utils.py* and *\_init\_.py* from
the /utils to one of the following locations:

-   For Python 2.7
    /usr/lib/python2.7/site-packages/ansible/module\_utils/storage/dell

-   For Python 3.5
    /usr/lib/python3.5/site-packages/ansible/module\_utils/storage/dell

  b\. Copy all the module python files from the /library folder to one
  of the following:

-   For Python 2.7
    /usr/lib/python2.7/site-packages/ansible/modules/storage/dellemc

-   For Python 3.5
    /usr/lib/python3.5/site-packages/ansible/modules/storage/dellemc/

c\. Copy the *dellemc\_powermax.py* from /doc\_fragments to one of the
following:

-   For Python 2.7
      /usr/lib/python2.7/site-packages/ansible/plugins/doc\_fragments

-   For Python 3.5
      /usr/lib/python3.5/site-packages/ansible/plugins/doc\_fragments/

  **NOTE:** The path may vary depending on the Python library version
  and the operating system.
>
  **Configure Ansible**
>
  **3**
>
  **Ansible modules for Dell EMC PowerMax**
>
  This chapter presents the following topics:

**Topics:**

-   Gather Facts module

-   Storage group module

-   Volume module

-   Host module

-   Host group module

-   Port module

-   Port Group module

-   Masking View module

-   Snapshot module

-   SRDF Module

-   RDF Group module

Gather Facts module
===================

  The Gather Facts module displays a list of specific entities in
  PowerMax array. The Gather facts module is used with Ansible to
  register values that are used in conditional statements within the
  playbooks.
>
  The Gather Facts module supports two sets of operations.

-   Operations on the Unisphere server

-   Operations on the PowerMax array registered under an Unisphere
    server

  On the Unisphere host, the Gather Facts module lists the registered
  storage arrays that are managed by the Unisphere host.
>
  On the PowerMax array, the Gather Facts module lists the following
  entities:

-   Arrays in an Unisphere host

-   Volumes in a specific array

-   Storage groups in a specific array

-   Hosts in a specific array

-   Host groups in a specific array

-   Storage resource pools in a specific array

-   Ports in a specific array

-   Port groups in a specific array

-   Masking views in a specific array

-   RDF groups in a specific array

-   Health status of the array

-   Support for generic filters for PowerMax array entities

Get list of volumes
-------------------

  The user can get the list of volumes and TDEV volumes in the storage
  array by running the appropriate playbook.
>
  The syntax of the playbook is as follows:
>
  \- name: Get list of volumes dellemc\_powermax\_gatherfacts:
  unispherehost: "{{unispherehost}}" universion: "{{universion}}"
>
  verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}"
  serial\_no: "{{serial\_no}}" tdev\_volumes: "True" gather\_subset: -
  vol
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Get list of arrays
------------------

  The user can get the list of registered storage arrays that are
  managed by the Unisphere host by running the appropriate playbook.
>
  The syntax for the playbook is shown as follows:
>
  \- name: Get array list dellemc\_powermax\_gatherfacts: unispherehost:
  "{{unispherehost}}" universion: "{{universion}}" verifycert:
  "{{verifycert}}" user: "{{user}}" password: "{{password}}"
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Get list of storage group
-------------------------

  The user can get the list of storage groups in the array by running
  the appropriate playbook.
>
  The syntax for the playbook is shown as follows:
>
  \- name: Get list of Storage groups dellemc\_powermax\_gatherfacts:
  unispherehost: "{{unispherehost}}" universion: "{{universion}}"
  verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}"
  serial\_no: "{{serial\_no}}" gather\_subset: - sg
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Get list of storage resource pool
---------------------------------

  The user can get the list of storage resource pools, and the details
  of each storage resource pool in the array by running the appropriate
  playbook.
>
  The syntax for the playbook is shown as follows:
>
  \- name: Get list of Storage Resource Pools
  dellemc\_powermax\_gatherfacts: unispherehost: "{{unispherehost}}"
  universion: "{{universion}}" verifycert: "{{verifycert}}" user:
  "{{user}}" password: "{{password}}"
>
  serial\_no: "{{serial\_no}}" gather\_subset: - srp
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Get list of port groups
-----------------------

  The user can get the list of port groups in the array by running the
  appropriate playbook.
>
  The syntax for the playbook is shown as follows:
>
  \- name: Get list of Port Groups dellemc\_powermax\_gatherfacts:
  unispherehost: "{{unispherehost}}" universion: "{{universion}}"
  verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}"
  serial\_no: "{{serial\_no}}" gather\_subset: - pg
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Get list of hosts
-----------------

  The user can get the list of hosts in the array by running the
  appropriate playbook.
>
  The syntax for the playbook is shown as follows:
>
  \- name: Get list of Hosts dellemc\_powermax\_gatherfacts:
  unispherehost: "{{unispherehost}}" universion: "{{universion}}"
  verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}"
  serial\_no: "{{serial\_no}}" gather\_subset: - host
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Get list of host groups
-----------------------

  The user can get the list of host groups in the array by running the
  appropriate playbook.
>
  The syntax for the playbook is shown as follows:
>
  \- name: Get list of Host Groups dellemc\_powermax\_gatherfacts:
  unispherehost: "{{unispherehost}}" universion: "{{universion}}"
  verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}"
  serial\_no: "{{serial\_no}}" gather\_subset: - hg
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Get list of ports
-----------------

  The user can get the list of ports in the array by running the
  appropriate playbook.
>
  The syntax for the playbook is shown as follows:
>
  \- name: Get list of Ports dellemc\_powermax\_gatherfacts:
  unispherehost: "{{unispherehost}}" universion: "{{universion}}"
  verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}"
  serial\_no: "{{serial\_no}}" gather\_subset: - port
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Get list of masking views
-------------------------

  The user can get the list of masking views available in the storage
  array by running the appropriate playbook.
>
  The syntax for the playbook is shown as follows:
>
  \- name: Get list of Maskng Views dellemc\_powermax\_gatherfacts:
  unispherehost: "{{unispherehost}}" universion: "{{universion}}"
  verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}"
  serial\_no: "{{serial\_no}}" gather\_subset: - mv
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Get list of RDF groups
----------------------

  The user can get the list of RDF groups in the array by running the
  appropriate playbook.
>
  The syntax for the playbook is shown as follows:

-   name: Get list of all RDF Groups of given PowerMax/VMAX Storage
    System dellemc\_powermax\_gatherfacts: unispherehost:
    "{{unispherehost}}" serial\_no: "{{serial\_no}}" universion:
    "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}"
    password: "{{password}}" gather\_subset: - rdf

  register: subset\_result

-   debug: var: subset\_result

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Get array health status
-----------------------

  The user can get the health status of the storage arrays that are
  managed by the Unisphere host by running the appropriate playbook.
>
  The syntax of the playbook is as follows:
>
  \- name: Get array health status dellemc\_powermax\_gatherfacts:
  unispherehost: "{{unispherehost}} "universion: "{{universion}}"
  verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}"
  serial\_no: "{{serial\_no}}" gather\_subset: - health
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Get list of volumes and storage groups with filter
--------------------------------------------------

  The user can get the list of volumes and storage groups, with
  appropriate filter, in the arrays that are managed by the Unisphere
  host by running the appropriate playbook.
>
  The syntax of the playbook is as follows:

<table>
<tbody>
<tr class="odd">
<td><ul>
<li><p>name: Get list of volumes and storage groups with filter dellemc_powermax_gatherfacts: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}" gather_subset:</p></li>
<li><p>vol - sg filters:</p></li>
<li><p>filter_key: "tdev" filter_operator: "equal" filter_value: "True" - filter_key: "cap_gb" filter_operator: "equal" filter_value: "5"</p></li>
</ul></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Gather Facts module parameters
------------------------------

  The following table provides the information about the parameters that
  are displayed on the console, when the user runs the *playbook* using
  the Gather facts module:

### Table 2. Parameters 

<table>
<thead>
<tr class="header">
<th><strong>Parameter</strong></th>
<th><strong>Choices/default</strong></th>
<th><strong>Comments</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>unispherehost</td>
<td></td>
<td>IP or FQDN of the Unisphere host. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>universion</td>
<td><ul>
<li><p>91</p></li>
<li><p>92</p></li>
</ul></td>
<td>The version of the Unisphere software. This parameter is optional.</td>
</tr>
<tr class="odd">
<td>verifycert</td>
<td>● True ● False</td>
<td><p>To validate the SSL certificate.</p>
<ul>
<li><p>True - Verify the SSL certificate.</p></li>
<li><p>False - Do not verify the SSL certificate.</p></li>
</ul>
<p>This parameter is mandatory.</p></td>
</tr>
<tr class="even">
<td>user</td>
<td></td>
<td>The user name to access the Unisphere server. The user name can be encrypted using Ansible vault. This parameter is mandatory.</td>
</tr>
<tr class="odd">
<td>password</td>
<td></td>
<td>The password to access the Unisphere server. The password can be encrypted using Ansible vault. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>serial_no</td>
<td></td>
<td>The serial number of the PowerMax array. If this parameter is absent, the script lists all the serial numbers of the registered array on the specified Unisphere host. This parameter is optional.</td>
</tr>
<tr class="odd">
<td>gather_subset</td>
<td><ul>
<li><p>vol</p></li>
<li><p>srp</p></li>
<li><p>sg</p></li>
<li><p>pg</p></li>
<li><p>host</p></li>
<li><p>hg</p></li>
<li><p>port</p></li>
<li><p>mv</p></li>
<li><p>rdf</p></li>
<li><p>health</p></li>
</ul></td>
<td><p>List of string variables to specify the PowerMax entities for which the information is required. Required only if serial_no is present.</p>
<ul>
<li><p>vol - volumes</p></li>
<li><p>srp - storage resource pools</p></li>
<li><p>sg - storage groups</p></li>
<li><p>pg - port groups</p></li>
<li><p>host - hosts</p></li>
<li><p>hg - host groups</p></li>
<li><p>port - ports</p></li>
<li><p>mv - masking views</p></li>
<li><p>rdf - RDF groups</p></li>
<li><p>health - health status of a specific PowerMax array</p></li>
</ul></td>
</tr>
<tr class="even">
<td>tdev_volumes</td>
<td>● True ● False</td>
<td>This parameter supports a boolean variable. By setting the value of this parameter to <em>True</em>, only TDEV Volumes will be listed. The default value of this parameter is <em>True</em>.</td>
</tr>
<tr class="odd">
<td>filters</td>
<td></td>
<td></td>
</tr>
<tr class="even">
<td>filter_key</td>
<td></td>
<td>Name identifier of the filter.</td>
</tr>
</tbody>
</table>

### Table 2. Parameters (continued)

<table>
<thead>
<tr class="header">
<th><strong>Parameter</strong></th>
<th><strong>Choices/default</strong></th>
<th><strong>Comments</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td></td>
<td></td>
<td><blockquote>
<p><strong>NOTE:</strong  Filters are applicable only when it is a valid filter_key, else the SDK will ignore it and return the usual result.</p>
<p>If a valid filter_key is passed and the given condition does not match, then an empty list is generated in the output.</p>
</blockquote></td>
</tr>
<tr class="even">
<td>filter_operator</td>
<td><ul>
<li><p>equal</p></li>
<li><p>greater</p></li>
<li><p>lesser</p></li>
<li><p>like</p></li>
</ul></td>
<td>Operation to be performed on filter key.</td>
</tr>
<tr class="odd">
<td>filter_value</td>
<td></td>
<td><p>Value of the filter key.</p>
<blockquote>
<p><strong>NOTE:</strong  When the filter_value is given as <em>True</em  or <em>False</em>, then the</p>
<p>filter_operator is ignored</p>
<p>irrespective of its value, because the SDK treats the value as bool type. filters:</p>
<p>- filter_key: tdev filter_operator: equal filter_value: True</p>
</blockquote></td>
</tr>
</tbody>
</table>

Storage group module
====================

  The Storage group module manages the storage groups available on the
  PowerMax storage array.
>
  The storage group module has the following functionalities:

-   List the volumes of a storage group.

-   Create a storage group.

-   Delete an existing storage group.

-   Add existing volumes to a storage group.

-   Remove existing volumes from a storage group.

-   Create volumes in a storage group.

-   Modify the storage group attributes.

-   Add child storage group to a parent storage group.

-   Remove child storage group from a parent storage group.

-   Add new volumes to SRDF protected storage group.

-   Remove volumes from SRDF protected storage group.

Get details of storage group including the volumes
--------------------------------------------------

  The user can get the details of a storage group in the array. The
  details include the list of volumes within the storage group.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Get storage group details including volumes
  dellemc\_powermax\_storagegroup:
>
  unispherehost: "{{unispherehost}}"
>
  universion: "{{universion}}" verifycert: "{{verifycert}}" user:
  "{{user}}" password: "{{password}}" serial\_no: "{{serial\_no}}"
  sg\_name: "ansible\_sg" state: "present"
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Create empty storage group
--------------------------

  The user can create an empty storage group by running the appropriate
  playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Create empty storage group dellemc\_powermax\_storagegroup:
  unispherehost: "{{unispherehost}}" universion: "{{universion}}"
  verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}"
  serial\_no: "{{serial\_no}}" sg\_name: "foo" service\_level: "Diamond"
  srp: "SRP\_1" compression: True state: "present"
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Delete empty storage group
--------------------------

  The user can delete an empty storage group by running the appropriate
  playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Delete the storage Group dellemc\_powermax\_storagegroup:
  unispherehost: "{{unispherehost}}" universion: "{{universion}}"
  verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}"
  serial\_no: "{{serial\_no}}" sg\_name: "foo" state: "absent"
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Add existing volumes to the existing storage group
--------------------------------------------------

  The user can add one or more existing volumes to a storage group by
  running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:

-   name: Adding existing volume(s) to existing SG
    dellemc\_powermax\_storagegroup:

  unispherehost: "{{unispherehost}}"
>
  universion: "{{universion}}" verifycert: "{{verifycert}}" user:
  "{{user}}" password: "{{password}}" serial\_no: "{{serial\_no}}"
  sg\_name: "foo" state: "present" volumes:

-   vol\_id: "00028"

-   vol\_id: "00018" - vol\_id: "00025" vol\_state: "present-in-group"

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Add new volumes to SRDF protected storage group
-----------------------------------------------

  The user can add volumes to a SRDF protected storage group by running
  the appropriate playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><ul>
<li><p>name: Add volumes to SRDF protected storage group dellemc_powermax_storagegroup: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}" sg_name: "{{sg_name}}" state: "present" volumes:</p></li>
<li><p>vol_name: "{{vol_name1}}" size: 1 cap_unit: "GB"</p></li>
<li><p>vol_name: "{{vol_name2}}" size: 1 cap_unit: "GB" vol_state: "present-in-group"</p></li>
</ul></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.
>
  **NOTE:** Add volumes to SRDF protected storage group is supported
  from PowerMax foxtail\_version (v5978.444.444) onwards.

Create new volumes for existing storage group
---------------------------------------------

  The user can create new volumes for an existing storage group by
  running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<thead>
<tr class="header">
<th><ul>
<li><p>name: Create new volumes for existing SG dellemc_powermax_storagegroup: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}" sg_name: "foo" state: "present" volumes:</p></li>
<li><p>vol_name: "foo" size: 1</p></li>
</ul></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p>cap_unit: "GB" - vol_name: "bar" size: 1 cap_unit: "GB"</p>
<p>vol_state: "present-in-group"</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Remove volumes from storage group
---------------------------------

  The user can remove one or multiple volumes from a storage group by
  running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:

-   name: Remove volume(s) from existing SG
    dellemc\_powermax\_storagegroup: unispherehost: "{{unispherehost}}"
    universion: "{{universion}}" verifycert: "{{verifycert}}" user:
    "{{user}}" password: "{{password}}" serial\_no: "{{serial\_no}}"
    sg\_name: "foo" state: "present" volumes:

-   vol\_id: "00028"

-   vol\_id: "00018" - vol\_name: "ansible-vol" vol\_state:
    "absent-in-group"

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Remove volumes from SRDF protected storage group
------------------------------------------------

  The user can remove multiple volumes from a SRDF protected storage
  group by running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><ul>
<li><p>name: Remove volumes from SRDF protected storage group dellemc_powermax_storagegroup: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}" sg_name: "{{sg_name}}" state: "present" volumes:</p></li>
<li><p>vol_name: "{{vol_name1}}" - vol_name: "{{vol_name2}}" vol_state: "absent-in-group"</p></li>
</ul></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Add child storage group to parent storage group
-----------------------------------------------

  The user can add a child storage group to a parent storage group by
  running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><ul>
<li><p>name: Adding child SG to parent SG dellemc_powermax_storagegroup: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}" sg_name: "parent_sg" state: "present" child_storage_groups:</p></li>
<li><p>"pie" - "bar"</p></li>
</ul>
<p>child_sg_state: "present-in-group"</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Remove child storage group from parent storage group
----------------------------------------------------

  The user can remove a child storage group from a parent storage group
  by running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><ul>
<li><p>name: Removing child SG from parent SG dellemc_powermax_storagegroup: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}" sg_name: "parent_sg":</p></li>
</ul>
<p>state: "present" child_storage_groups:</p>
<ul>
<li><p>"pie" - "bar"</p></li>
</ul>
<p>child_sg_state: "absent-in-group"</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Rename storage group
--------------------

  The user can rename a storage group by running the appropriate
  playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Rename Storage Group dellemc\_powermax\_storagegroup:
  unispherehost: "{{unispherehost}}" universion: "{{universion}}"
  verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}"
  serial\_no: "{{serial\_no}}" sg\_name: "ansible\_sg":
>
  new\_sg\_name: "ansible\_sg\_renamed" state: "present"
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Storage Group module parameters
-------------------------------

  The following table lists the parameters that must be set before the
  user runs the playbook for the Storage Group module: **Table 3.
  Parameters**

<table>
<thead>
<tr class="header">
<th><strong>Parameter</strong></th>
<th><strong>Choices/default</strong></th>
<th><strong>Comments</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>unispherehost</td>
<td></td>
<td>IP or FQDN of the Unisphere host. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>universion</td>
<td><ul>
<li><p>91</p></li>
<li><p>92</p></li>
</ul></td>
<td>The version of the Unisphere software. This parameter is optional.</td>
</tr>
<tr class="odd">
<td>verifycert</td>
<td>● True ● False</td>
<td><p>To validate the SSL certificate.</p>
<ul>
<li><p>True - Verifies the SSL certificate.</p></li>
<li><p>False - Specifies that the SSL certificate should not be verified.</p></li>
</ul>
<p>This parameter is mandatory.</p></td>
</tr>
<tr class="even">
<td>user</td>
<td></td>
<td>The user name to access the Unisphere server. The user name can be encrypted using Ansible vault. This parameter is mandatory.</td>
</tr>
<tr class="odd">
<td>password</td>
<td></td>
<td>The password to access the Unisphere server. The password can be encrypted using Ansible vault. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>serial_no</td>
<td></td>
<td>The serial number of the PowerMax array. If this parameter is absent, the script lists all the serial numbers of the registered array on the specified Unisphere host. This parameter is mandatory.</td>
</tr>
<tr class="odd">
<td>sg_name</td>
<td></td>
<td>The name of the storage group. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>new_sg_name</td>
<td></td>
<td>The new name of the storage group.</td>
</tr>
<tr class="odd">
<td>service_level</td>
<td></td>
<td>The name of the service level</td>
</tr>
<tr class="even">
<td>srp</td>
<td></td>
<td>The name of the storage resource pool. This parameter is ignored if the service_level is not specified. The default value is the name of the default storage resource pool of the array.</td>
</tr>
<tr class="odd">
<td>compression</td>
<td><ul>
<li><p>true</p></li>
<li><p>false</p></li>
</ul>
<p>The default value is true.</p></td>
<td>Defines if the compression is enable for a storage group. This parameter is unavailable if the service_level is not specified.</td>
</tr>
<tr class="even">
<td>state</td>
<td><ul>
<li><p>absent</p></li>
<li><p>present</p></li>
</ul></td>
<td>Defines whether the storage group should exist or not. This parameter is mandatory.</td>
</tr>
</tbody>
</table>

### Table 3. Parameters (continued)

<table>
<thead>
<tr class="header">
<th><strong>Parameter</strong></th>
<th><strong>Choices/default</strong></th>
<th><strong>Comments</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>volumes</td>
<td></td>
<td><p>This parameter lists the volumes present in the storage group. Each volume has four attributes.</p>
<ul>
<li><p>vol_name</p></li>
<li><p>size</p></li>
<li><p>cap_unit</p></li>
<li><p>vol_id</p></li>
</ul>
<p>Use either volume name or volume ID to identify the volumes. Both cannot be used simultaneously to identify the volumes. For new volumes that are added to storage group, the name and size must be provided. This parameter is optional.</p></td>
</tr>
<tr class="even">
<td>vol_state</td>
<td><ul>
<li><p>present-in-group</p></li>
<li><p>absent-in-group</p></li>
</ul></td>
<td>Defines the state of the volumes inside the storage group.</td>
</tr>
<tr class="odd">
<td>child_storage_groups</td>
<td></td>
<td>Lists the child storage group.</td>
</tr>
<tr class="even">
<td>child_sg_state</td>
<td><ul>
<li><p>present-in-group</p></li>
<li><p>absent-in-group</p></li>
</ul></td>
<td>Describes the state of child storage group in a parent storage group.</td>
</tr>
</tbody>
</table>

Volume module
=============

  The Volume module manages the storage volumes on PowerMax arrays.
>
  The volume module has the following capabilities:

-   Create volume.

-   Expand volume.

-   Rename volume.

-   Delete volume using the volume ID.

-   Move volumes between storage groups. ● Get volume details.

  The volume module has the following capabilities using WWN:

-   Expand volume.

-   Rename volume.

-   Delete volume using the volume ID.

-   Move volumes between storage groups.

-   Get volume details.

-   Add new volume to SRDF protected storage group.

-   Expand volume which is part of SRDF protected storage group.

Create volume
-------------

  The user can create a volume in the storage group by running the
  appropriate playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Create volume dellemc\_powermax\_volume: unispherehost:
  "{{unispherehost}}" universion: "{{universion}}" verifycert:
  "{{verifycert}}"
>
  user: "{{user}}" password: "{{password}}" serial\_no: "{{serial\_no}}"
  vol\_name: "{{vol\_name}}" sg\_name: "{{sg\_name}}" size: 1 cap\_unit:
  "{{cap\_unit}}" state: 'present'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Expand volume
-------------

  The user can expand the size of the volumes by running the appropriate
  playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Expand volume size dellemc\_powermax\_volume: unispherehost:
  "{{unispherehost}}" universion: "{{universion}}" verifycert:
  "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial\_no:
  "{{serial\_no}}" size: 3 cap\_unit: "{{cap\_unit}}" vol\_id: "0059B"
  state: 'present'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Rename volume
-------------

  The user can rename the volume by running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Rename volume dellemc\_powermax\_volume: unispherehost:
  "{{unispherehost}}" universion: "{{universion}}" verifycert:
  "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial\_no:
  "{{serial\_no}}" new\_name: "{{new\_vol\_name}}" vol\_id: "0059B"
  state: 'present'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Delete volume
-------------

  The user can delete the volume by running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Delete volume dellemc\_powermax\_volume: unispherehost:
  "{{unispherehost}}" universion: "{{universion}}" verifycert:
  "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial\_no:
  "{{serial\_no}}" vol\_id: "0059B" state: 'absent'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Move volumes between storage group
----------------------------------

  The user can move the volumes from one storage group to another by
  running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Move volume between storage group dellemc\_powermax\_volume:
  unispherehost: "{{unispherehost}}" universion: "{{universion}}"
  verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}"
  serial\_no: "{{serial\_no}}" vol\_name: "{{vol\_name}}" sg\_name:
  "{{sg\_name}}" new\_sg\_name: "{{new\_sg\_name}}" state: 'present'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Add new volume to SRDF protected storage group
----------------------------------------------

  The user can add a volume to the SRDF protected storage group by
  running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Add new volume to SRDF protected storage group
  dellemc\_powermax\_volume: unispherehost: "{{unispherehost}}"
  universion: "{{universion}}" verifycert: "{{verifycert}}" user:
  "{{user}}" password: "{{password}}" serial\_no: "{{serial\_no}}"
  vol\_name: "{{vol\_name}}" sg\_name: "{{sg\_name}}" size: 1 cap\_unit:
  "{{cap\_unit}}" state: 'present'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.
>
  **NOTE:** Add volume to SRDF protected storage group is supported from
  PowerMax foxtail\_version (v5978.444.444) onwards.

Expand volume of SRDF protected storage group using volume name
---------------------------------------------------------------

  The user can expand volume of SRDF protected storage group using
  volume name by running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Expand volume of SRDF protected storage group using volume
  name dellemc\_powermax\_volume: unispherehost: "{{unispherehost}}"
  universion: "{{universion}}" verifycert: "{{verifycert}}" user:
  "{{user}}" password: "{{password}}" serial\_no: "{{serial\_no}}"
  vol\_name: "{{vol\_name}}" sg\_name: "{{sg\_name}}" size: 8 cap\_unit:
  "{{cap\_unit}}" state: 'present'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.
>
  **NOTE:** Expand volume of SRDF protected storage group using volume
  name is supported from PowerMax foxtail\_version (v5978.444.444)
  onwards.

Expand volume of SRDF protected storage group using volume identifier
---------------------------------------------------------------------

  The user can expand volume of SRDF protected storage group using
  identifier by running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Expand volume of SRDF protected storage group using volume
  identifier dellemc\_powermax\_volume: unispherehost:
  "{{unispherehost}}" universion: "{{universion}}" verifycert:
  "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial\_no:
  "{{serial\_no}}" vol\_id: "{{vol\_id}}" size: 8 cap\_unit:
  "{{cap\_unit}}" state: 'present'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.
>
  **NOTE:** Expand volume of SRDF protected storage group using volume
  identifier is supported from PowerMax foxtail\_version (v5978.444.444)
  onwards.

Get volume using WWN
--------------------

  The user can get details of a volume using WWN by running the
  appropriate playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Get volume details dellemc\_powermax\_volume: unispherehost:
  "{{unispherehost}}" universion: "{{universion}}"

<table>
<tbody>
<tr class="odd">
<td><p>verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}"</p>
<p>vol_wwn: "{{result.volume_details.wwn}}" state: "present"</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Expand volume using WWN
-----------------------

  The user can expand the size of the volumes using WWN by running the
  appropriate playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><p>- name: Expand volume using wwn dellemc_powermax_volume: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}" size: 21</p>
<p>cap_unit: "{{cap_unit}}"</p>
<p>vol_wwn: "{{result.volume_details.wwn}}" state: “present”</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Move volumes between storage groups using WWN
---------------------------------------------

  The user can move the volumes using WWN, from one storage group to
  another by running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Move volume between Storage group dellemc\_powermax\_volume:
  unispherehost: "{{unispherehost}}" universion: "{{universion}}"
  verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}"
  serial\_no: "{{serial\_no}}" vol\_wwn:
  "{{result.volume\_details.wwn}}" sg\_name: "{{sg\_name}}"
  new\_sg\_name: "{{new\_sg\_name}}" state: “present”
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Rename volume using WWN
-----------------------

  The user can rename the volume using WWN by running the appropriate
  playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Rename volume dellemc\_powermax\_volume: unispherehost:
  "{{unispherehost}}" universion: "{{universion}}" verifycert:
  "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial\_no:
  "{{serial\_no}}" new\_name: "Ansible\_Testing\_Renamed" vol\_wwn:
  "{{result.volume\_details.wwn}}" state: "present"
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Delete volume using WWN
-----------------------

  The user can delete the volume using WWN by running the appropriate
  playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><p>- name: Delete volume dellemc_powermax_volume: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}"</p>
<p>vol_wwn: "{{result.volume_details.wwn}}" state: "absent"</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Volume module parameters
------------------------

  The parameters of the Volume module are listed as follows:

### Table 4. Parameters 

<table>
<thead>
<tr class="header">
<th><strong>Parameter</strong></th>
<th><strong>Choices/default</strong></th>
<th><strong>Comments</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>unispherehost</td>
<td></td>
<td>IP or FQDN of the Unisphere host. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>universion</td>
<td><ul>
<li><p>91</p></li>
<li><p>92</p></li>
</ul></td>
<td>The version of the Unisphere software. This parameter is optional.</td>
</tr>
<tr class="odd">
<td>verifycert</td>
<td>● True ● False</td>
<td><p>To validate the SSL certificate.</p>
<ul>
<li><p>True - Verifies the SSL certificate.</p></li>
<li><p>False - Specifies that the SSL certificate should not be verified.</p></li>
</ul>
<p>This parameter is mandatory.</p></td>
</tr>
<tr class="even">
<td>user</td>
<td></td>
<td>The user name to access the Unisphere server. The user name can be encrypted using Ansible vault. This parameter is mandatory.</td>
</tr>
<tr class="odd">
<td>password</td>
<td></td>
<td>The password to access the Unisphere server. The password can be encrypted using Ansible vault. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>serial_no</td>
<td></td>
<td>The serial number of the PowerMax array. If this parameter is absent, the</td>
</tr>
</tbody>
</table>

### Table 4. Parameters (continued)

<table>
<thead>
<tr class="header">
<th><strong>Parameter</strong></th>
<th><strong>Choices/default</strong></th>
<th><strong>Comments</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td></td>
<td></td>
<td>script lists all the serial numbers of the registered array on the specified Unisphere host. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>vol_name</td>
<td></td>
<td>The name of the volume.</td>
</tr>
<tr class="odd">
<td>new_name</td>
<td></td>
<td>The new identifier for the volume.</td>
</tr>
<tr class="even">
<td>sg_name</td>
<td></td>
<td>The name of the current storage group.</td>
</tr>
<tr class="odd">
<td>new_sg_name</td>
<td></td>
<td>The name of the target storage group for moving volumes from one storage group to another.</td>
</tr>
<tr class="even">
<td>size</td>
<td></td>
<td>The desired size of the volume. This parameter is mandatory when you create or expand the volume. Shrinking of volumes is not supported.</td>
</tr>
<tr class="odd">
<td>cap_unit</td>
<td><ul>
<li><p>MB</p></li>
<li><p>GB ● TB</p></li>
</ul>
<p>The default unit is <em>GB</em>.</p></td>
<td>Volume capacity unit.</td>
</tr>
<tr class="even">
<td>vol_id</td>
<td></td>
<td>The native id of the volume. This parameter is optional.</td>
</tr>
<tr class="odd">
<td>state</td>
<td><ul>
<li><p>absent</p></li>
<li><p>present</p></li>
</ul></td>
<td>Defines whether the volume should exist in the storage group. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>vol_wwn</td>
<td></td>
<td>The external WWN of the volume. This parameter is optional.</td>
</tr>
</tbody>
</table>

Host module
===========

  The host module manages the host within the PowerMax array.
>
  The host module has the following functions:

-   Create host with initiators and host flags.

-   Add initiators to the host.

-   Remove initiators from the host.

-   Modify host flag values.

-   Rename host. ● Delete host.

Create host
-----------

  The user can create a host by running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Create host dellemc\_powermax\_host: unispherehost:
  "{{unispherehost}}" universion: "{{universion}}" verifycert:
  "{{verifycert}}" user: "{{user}}" password: "{{password}}"
>
  serial\_no: "{{serial\_no}}" host\_name: "{{host\_name}}" initiators:
  - 10000090fa7b4e85 host\_flags: spc2\_protocol\_version: true
  consistent\_lun: true volume\_set\_addressing: 'unset'
  disable\_q\_reset\_on\_ua: false openvms: 'unset' state: 'present'
  initiator\_state: 'present-in-host'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Get details of the host
-----------------------

  The user can get details of the host by running the appropriate
  playbook.
>
  The syntax of the playbook is shown as follows:
>
  -name: Get host details dellemc\_powermax\_host:
>
  unispherehost: "{{unispherehost}}" universion: "{{universion}}"
  verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}"
  serial\_no: "{{serial\_no}}" host\_name: "{{host\_name}}" state:
  'present'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Add initiator to host
---------------------

  The user can add an initiator to the host by running the appropriate
  playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Adding initiator to host dellemc\_powermax\_host:
  unispherehost: "{{unispherehost}}" universion: "{{universion}}"
  verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}"
  serial\_no: "{{serial\_no}}" host\_name: "{{host\_name}}" initiators:
  - 10000090fa3d303e
>
  initiator\_state: 'present-in-host' state: 'present'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Remove initiators from host
---------------------------

  The user can remove initiators from the host by running the
  appropriate playbook. The syntax of the playbook is shown as follows:
>
  \- name: Removing initiator from host dellemc\_powermax\_host:
  unispherehost: "{{unispherehost}}" universion: "{{universion}}"
  verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}"
  serial\_no: "{{serial\_no}}" host\_name: "{{host\_name}}" initiators:
  - 10000090fa3d303e
>
  initiator\_state: 'absent-in-host' state: 'present'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Modify host flags
-----------------

  The user can modify the host flags by running the appropriate
  playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Modify flags of host dellemc\_powermax\_host: unispherehost:
  "{{unispherehost}}" universion: "{{universion}}" verifycert:
  "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial\_no:
  "{{serial\_no}}" host\_name: "{{host\_name}}" host\_flags:
  spc2\_protocol\_version: unset consistent\_lun: unset
  volume\_set\_addressing: true disable\_q\_reset\_on\_ua: false
  openvms: false
>
  avoid\_reset\_broadcast: true state: 'present'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Rename host
-----------

  The user can rename the host by running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Rename host dellemc\_powermax\_host: unispherehost:
  "{{unispherehost}}" universion: "{{universion}}" verifycert:
  "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial\_no:
  "{{serial\_no}}" host\_name: "{{host\_name}}" new\_name:
  "{{new\_host\_name}}" state: 'present'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Delete host
-----------

  The user can delete the host by running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Delete host dellemc\_powermax\_host: unispherehost:
  "{{unispherehost}}" universion: "{{universion}}" verifycert:
  "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial\_no:
  "{{serial\_no}}" host\_name: "{{new\_host\_name}}" state: 'absent'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Host module parameters
----------------------

  The parameters of the Host module are listed as follows:

### Table 5. Parameters 

<table>
<thead>
<tr class="header">
<th><strong>Parameter</strong></th>
<th><strong>Choice/default</strong></th>
<th><strong>Comments</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>unispherehost</td>
<td></td>
<td>IP or FQDN of the Unisphere host. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>universion</td>
<td><ul>
<li><p>91</p></li>
<li><p>92</p></li>
</ul></td>
<td>The version of the Unisphere software. This parameter is optional.</td>
</tr>
<tr class="odd">
<td>verifycert</td>
<td>● True ● False</td>
<td><p>To validate the SSL certificate.</p>
<ul>
<li><p>True - Verifies the SSL certificate.</p></li>
<li><p>False - Specifies that the SSL certificate should not be verified.</p></li>
</ul>
<p>This parameter is mandatory.</p></td>
</tr>
<tr class="even">
<td>user</td>
<td></td>
<td>The user name to access the Unisphere server. The user name can be encrypted using Ansible vault. This parameter is mandatory.</td>
</tr>
<tr class="odd">
<td>password</td>
<td></td>
<td>The password to access the Unisphere server. The password can be encrypted using Ansible vault. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>serial_no</td>
<td></td>
<td>The serial number of the PowerMax array. If this parameter is absent, the script lists all the serial numbers of the registered array on the specified Unisphere host. This parameter is mandatory.</td>
</tr>
</tbody>
</table>

### Table 5. Parameters (continued)

<table>
<thead>
<tr class="header">
<th><strong>Parameter</strong></th>
<th><strong>Choice/default</strong></th>
<th><strong>Comments</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>host_name</td>
<td></td>
<td><p>The name of the host. The following conditions are applicable when naming the host:</p>
<ul>
<li><p>Do not use special characters except "<em>_</em>."</p></li>
<li><p>Case sensitive for RestAPI calls.</p></li>
</ul>
<p>This parameter is mandatory.</p></td>
</tr>
<tr class="even">
<td>new_name</td>
<td></td>
<td><p>The new name of the host when you rename the host. The following conditions must be met when you enter a new name:</p>
<ul>
<li><p>Do not use special characters except "<em>_</em>."</p></li>
<li><p>Case sensitive for RestAPI calls.</p></li>
</ul></td>
</tr>
<tr class="odd">
<td>initiators</td>
<td></td>
<td>Lists the initiator <em>WWN</em  or <em>IQN</em  that needs to be added to or removed from the host.</td>
</tr>
<tr class="even">
<td>host_flags</td>
<td><ul>
<li><p>yes</p></li>
<li><p>no</p></li>
<li><p>unset</p></li>
</ul>
<p>The default parameter is <em>unset</em>.</p></td>
<td><p>Enter as in <em>yaml</em  dictionary. The host_flags are optional. All the host_flags are listed below.</p>
<ul>
<li><p>volume_set_addressing</p></li>
<li><p>disable_q_reset_on_ua</p></li>
<li><p>environ_set</p></li>
<li><p>avoid_reset_broadcast</p></li>
<li><p>openvms</p></li>
<li><p>scsi_3</p></li>
<li><p>spc2_protocol_version</p></li>
<li><p>scsi_support1</p></li>
<li><p>consistent_lun</p></li>
</ul></td>
</tr>
<tr class="odd">
<td>state</td>
<td><ul>
<li><p>absent</p></li>
<li><p>present</p></li>
</ul></td>
<td><p>Defines whether the host must exist in the system.</p>
<ul>
<li><p>absent - indicates that the host must not exist in the system.</p></li>
<li><p>present - indicates that the host must exist in the system.</p></li>
</ul>
<p>This parameter is mandatory.</p></td>
</tr>
<tr class="even">
<td>initiator_state</td>
<td><ul>
<li><p>present-in-host</p></li>
<li><p>absent-in-host</p></li>
</ul></td>
<td><p>Defines whether the initiator must be available in the host.</p>
<ul>
<li><p>present-in-host - indicates that the initiator must be present in the host.</p></li>
<li><p>absent-in-host - indicates that the initiator must not be present in the host.</p></li>
</ul>
<p>This parameter is mandatory for the following conditions:</p>
<ul>
<li><p>Create a host with initiators.</p></li>
<li><p>Add initiators to a host.</p></li>
<li><p>Remove initiators from a host</p></li>
</ul></td>
</tr>
</tbody>
</table>

Host group module
=================

  The host group module manages the host group within the PowerMax
  array. A host group is a container for multiple hosts and enables
  simple configuration of clusters.
>
  The functions of the host group module are as follows:

-   Create host group with hosts.

-   Add hosts to a host group.

-   Remove hosts from a host group.

-   Rename host group.

-   Modify the host flags of a host group.

-   Delete host group.

Create host group
-----------------

  The user can create a host group by running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><ul>
<li><p>name: Create host group dellemc_powermax_hostgroup: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}" hostgroup_name: "{{hostgroup_name}}" hosts:</p></li>
<li><p>Ansible_Testing_host state: 'present'</p></li>
</ul>
<p>host_state: 'present-in-group' host_flags: spc2_protocol_version: true consistent_lun: true disable_q_reset_on_ua: false openvms: 'unset'</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Get details of host group
-------------------------

  The user can get the details of the host group by running the
  appropriate playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Get host group details dellemc\_powermax\_hostgroup:
  unispherehost: "{{unispherehost}}" universion: "{{universion}}"
  verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}"
  serial\_no: "{{serial\_no}}" hostgroup\_name: "{{hostgroup\_name}}"
  state: 'present'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Add host to host group
----------------------

  The user can add host to a host group by running the appropriate
  playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><ul>
<li><p>name: Adding host to host group dellemc_powermax_hostgroup: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}" hostgroup_name: "{{hostgroup_name}}" hosts:</p></li>
<li><p>Ansible_Testing_host2 state: 'present'</p></li>
</ul>
<p>host_state: 'present-in-group'</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Remove host from host group
---------------------------

  The user can remove a host from the host group by running the
  appropriate playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><ul>
<li><p>name: Removing host from host group dellemc_powermax_hostgroup: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}" hostgroup_name: "{{hostgroup_name}}" hosts:</p></li>
<li><p>Ansible_Testing_host2 state: 'present'</p></li>
</ul>
<p>host_state: 'absent-in-group'</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Modify host group flags
-----------------------

  The user can modify the host flags by running the appropriate
  playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Modify flags of host group dellemc\_powermax\_hostgroup:
  unispherehost: "{{unispherehost}}" universion: "{{universion}}"
  verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}"
  serial\_no: "{{serial\_no}}" hostgroup\_name: "{{hostgroup\_name}}"
  host\_flags: spc2\_protocol\_version: unset disable\_q\_reset\_on\_ua:
  false openvms: false
>
  avoid\_reset\_broadcast: true state: 'present'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Rename host group
-----------------

  The user can rename the host group by running the appropriate
  playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Rename host group dellemc\_powermax\_hostgroup:
  unispherehost: "{{unispherehost}}" universion: "{{universion}}"
  verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}"
  serial\_no: "{{serial\_no}}" hostgroup\_name: "{{hostgroup\_name}}"
  new\_name: "Ansible\_Testing\_hostgroup2" state: 'present'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Delete host group
-----------------

  The user can delete the host group by running the appropriate
  playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><p>- name: Delete host group dellemc_powermax_hostgroup: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}"</p>
<p>hostgroup_name: "Ansible_Testing_hostgroup2" state: 'absent'</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Host Group module parameters
----------------------------

  The parameters of the Host Group module are listed as follows with an
  example:

### Table 6. Parameters 

<table>
<thead>
<tr class="header">
<th><strong>Parameter</strong></th>
<th><strong>Choice/default</strong></th>
<th><strong>Comments</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>unispherehost</td>
<td></td>
<td>IP or FQDN of the Unisphere host. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>universion</td>
<td><ul>
<li><p>91</p></li>
<li><p>92</p></li>
</ul></td>
<td>The version of the Unisphere software. This parameter is optional.</td>
</tr>
</tbody>
</table>

### Table 6. Parameters (continued)

<table>
<thead>
<tr class="header">
<th><strong>Parameter</strong></th>
<th><strong>Choice/default</strong></th>
<th><strong>Comments</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>verifycert</td>
<td>● True ● False</td>
<td><p>To validate the SSL certificate.</p>
<ul>
<li><p>True - Verifies the SSL certificate.</p></li>
<li><p>False - Specifies that the SSL certificate should not be verified.</p></li>
</ul>
<p>This parameter is mandatory.</p></td>
</tr>
<tr class="even">
<td>user</td>
<td></td>
<td>The user name to access the Unisphere server. The user name can be encrypted using Ansible vault. This parameter is mandatory.</td>
</tr>
<tr class="odd">
<td>password</td>
<td></td>
<td>The password to access the Unisphere server. The password can be encrypted using Ansible vault. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>serial_no</td>
<td></td>
<td>The serial number of the PowerMax array. If this parameter is absent, the script lists all the serial numbers of the registered array on the specified Unisphere host. This parameter is mandatory.</td>
</tr>
<tr class="odd">
<td>host_group_name</td>
<td></td>
<td><p>The name of the host group. The following conditions must be met when you enter the name:</p>
<ul>
<li><p>Do not use special characters except "<em>_</em>."</p></li>
<li><p>Case sensitive for RestAPI calls.</p></li>
</ul>
<p>This parameter is mandatory.</p></td>
</tr>
<tr class="even">
<td>new_name</td>
<td></td>
<td><p>The new name of the host group when you rename the host group. The following conditions must be met when you enter a new name:</p>
<ul>
<li><p>Do not use special characters except "<em>_</em>."</p></li>
<li><p>Case sensitive for RestAPI calls.</p></li>
</ul></td>
</tr>
<tr class="odd">
<td>hosts</td>
<td></td>
<td>Lists of the host names that are added to the host group or removed from host group. You can create an empty host group.</td>
</tr>
<tr class="even">
<td>host_state</td>
<td><ul>
<li><p>present-in-group</p></li>
<li><p>absent-in-group</p></li>
</ul></td>
<td><p>Defines whether the host must be available in the host group.</p>
<ul>
<li><p>present-in-group - indicates that the host must be present in the host group.</p></li>
<li><p>absent-in-group - indicates that the host must not be present in the host group.</p></li>
</ul></td>
</tr>
<tr class="odd">
<td>host_flags</td>
<td><ul>
<li><p>yes</p></li>
<li><p>no</p></li>
<li><p>unset (default)</p></li>
</ul></td>
<td><p>Enter as in <em>yaml</em  dictionary. All the host_flags are listed below.</p>
<ul>
<li><p>volume_set_addressing</p></li>
<li><p>disable_q_reset_on_ua</p></li>
<li><p>environ_set</p></li>
</ul></td>
</tr>
</tbody>
</table>

### Table 6. Parameters (continued)

<table>
<thead>
<tr class="header">
<th><strong>Parameter</strong></th>
<th><strong>Choice/default</strong></th>
<th><strong>Comments</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td></td>
<td></td>
<td><ul>
<li><p>avoid_reset_broadcast</p></li>
<li><p>openvms</p></li>
<li><p>scsi_3</p></li>
<li><p>spc2_protocol_version</p></li>
<li><p>scsi_support1</p></li>
<li><p>consistent_lun</p></li>
</ul></td>
</tr>
<tr class="even">
<td>state</td>
<td><ul>
<li><p>absent</p></li>
<li><p>present</p></li>
</ul></td>
<td><p>Defines whether the host group must be present in the system.</p>
<ul>
<li><p>absent - The host must not be present in the system.</p></li>
<li><p>present - The host must be present in the system.</p></li>
</ul>
<p>This parameter is mandatory.</p></td>
</tr>
</tbody>
</table>

Port module
===========

  The ports available on the PowerMax array are managed by the Port
  module. The Port module lists the details of single or multiple ports.

Get details of single/multiple ports
------------------------------------

  The user can get the details of single or multiple ports by running
  the appropriate playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><ul>
<li><p>name: Get details of single/multiple ports dellemc_powermax_port: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{array_id}}" ports:</p></li>
<li><p>director_id: "FA-1D" port_id: "5"</p></li>
<li><p>director_id: "SE-1F" port_id: "29"</p></li>
</ul></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Port module parameters
----------------------

  The parameters for the Port module are listed as follows with an
  example:

### Table 7. Parameters 

<table>
<thead>
<tr class="header">
<th><strong>Parameter</strong></th>
<th><strong>Choice/default</strong></th>
<th><strong>Comments</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>unispherehost</td>
<td></td>
<td>IP or FQDN of the Unisphere host. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>universion</td>
<td><ul>
<li><p>91</p></li>
<li><p>92</p></li>
</ul></td>
<td>The version of the Unisphere software. This parameter is optional.</td>
</tr>
</tbody>
</table>

### Table 7. Parameters (continued)

<table>
<thead>
<tr class="header">
<th><strong>Parameter</strong></th>
<th><strong>Choice/default</strong></th>
<th><strong>Comments</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>verifycert</td>
<td>● True ● False</td>
<td><p>To validate the SSL certificate.</p>
<ul>
<li><p>True - Verifies the SSL certificate.</p></li>
<li><p>False - Specifies that the SSL certificate should not be verified.</p></li>
</ul>
<p>This parameter is mandatory.</p></td>
</tr>
<tr class="even">
<td>user</td>
<td></td>
<td>The user name to access the Unisphere server. The user name can be encrypted using Ansible vault. This parameter is mandatory.</td>
</tr>
<tr class="odd">
<td>password</td>
<td></td>
<td>The password to access the Unisphere server. The password can be encrypted using Ansible vault. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>serial_no</td>
<td></td>
<td>The serial number of the PowerMax array. If this parameter is absent, the script lists all the serial numbers of the registered array on the specified Unisphere host. This parameter is mandatory.</td>
</tr>
<tr class="odd">
<td>ports</td>
<td></td>
<td>Lists the port director and the port id.</td>
</tr>
</tbody>
</table>

Port Group module
=================

  The Port Group module manages the port group in the PowerMax array.
>
  The port group management module has the following functions:

-   Create a port group with ports.

-   Create empty port group.

-   Add ports to a port group.

-   Remove ports from a port group.

-   Rename a port group.

-   Remove a port group.

Create port group without ports
-------------------------------

  The user can create a port group without ports by running the
  appropriate playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Create port group without ports dellemc\_powermax\_portgroup:
  unispherehost: "{{unispherehost}}" universion: "{{universion}}"
  verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}"
  serial\_no: "{{array\_id}}" portgroup\_name: "{{portgroup\_name}}"
  state: "present"
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Create port group with ports
----------------------------

  The user can create a port group with ports by running the appropriate
  playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><ul>
<li><p>name: Create port group with ports dellemc_powermax_portgroup: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{array_id}}"</p></li>
</ul>
<p>portgroup_name: "{{portgroup_name}}" state: "present" ports:</p>
<ul>
<li><p>director_id: "FA-1D" port_id: "5"</p></li>
<li><p>director_id: "FA-2D" port_id: "5"</p></li>
</ul>
<p>port_state: "present-in-group"</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Add ports to port group
-----------------------

  The user can add ports to a port group by running the appropriate
  playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><ul>
<li><p>name: Add ports to port group dellemc_powermax_portgroup: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{array_id}}"</p></li>
</ul>
<p>portgroup_name: "{{portgroup_name}}" state: "present" ports:</p>
<ul>
<li><p>director_id: "FA-2D" port_id: "8"</p></li>
<li><p>director_id: "FA-2D" port_id: "9"</p></li>
</ul>
<p>port_state: "present-in-group"</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Remove ports from port group
----------------------------

  The user can remove ports from the port group by running the
  appropriate playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Remove ports from port group dellemc\_powermax\_portgroup:
  unispherehost: "{{unispherehost}}" universion: "{{universion}}"
  verifycert: "{{verifycert}}" user: "{{user}}"

<table>
<tbody>
<tr class="odd">
<td><p>password: "{{password}}" serial_no: "{{array_id}}"</p>
<p>portgroup_name: "{{portgroup_name}}" state: "present" ports:</p>
<ul>
<li><p>director_id: "FA-2D" port_id: "8"</p></li>
<li><p>director_id: "FA-2D" port_id: "9"</p></li>
</ul>
<p>port_state: "absent-in-group"</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Rename port group
-----------------

  The user can rename the port group by running the appropriate
  playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><p>- name: Modify port group dellemc_powermax_portgroup: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{array_id}}"</p>
<p>portgroup_name: "{{portgroup_name}}" state: "present" new_name: "{{new_name}}"</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Delete port group
-----------------

  The user can delete a port group by running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><p>- name: Delete port group dellemc_powermax_portgroup: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{array_id}}"</p>
<p>portgroup_name: "{{portgroup_name}}" state: "absent"</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Port Group module parameters
----------------------------

  The parameters for the Port Group module are listed as follows with an
  example:

### Table 8. Parameters 

<table>
<thead>
<tr class="header">
<th><strong>Parameter</strong></th>
<th><strong>Choice/default</strong></th>
<th><strong>Comments</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>unispherehost</td>
<td></td>
<td>IP or FQDN of the Unisphere host. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>universion</td>
<td><ul>
<li><p>91</p></li>
<li><p>92</p></li>
</ul></td>
<td>The version of the Unisphere software. This parameter is optional.</td>
</tr>
<tr class="odd">
<td>verifycert</td>
<td>● True ● False</td>
<td><p>To validate the SSL certificate.</p>
<ul>
<li><p>True - Verifies the SSL certificate.</p></li>
<li><p>False - Specifies that the SSL certificate should not be verified.</p></li>
</ul>
<p>This parameter is mandatory.</p></td>
</tr>
<tr class="even">
<td>user</td>
<td></td>
<td>The user name to access the Unisphere server. The user name can be encrypted using Ansible vault. This parameter is mandatory.</td>
</tr>
<tr class="odd">
<td>password</td>
<td></td>
<td>The password to access the Unisphere server. The password can be encrypted using Ansible vault. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>serial_no</td>
<td></td>
<td>The serial number of the PowerMax array. If this parameter is absent, the script lists all the serial numbers of the registered array on the specified Unisphere host. This parameter is mandatory.</td>
</tr>
<tr class="odd">
<td>portgroup_name</td>
<td></td>
<td><p>The name of the port group. The following conditions must be met when you enter the name:</p>
<ul>
<li><p>Do not use special characters except "<em>_</em>."</p></li>
<li><p>Case sensitive for RestAPI calls.</p></li>
</ul>
<p>This parameter is mandatory.</p></td>
</tr>
<tr class="even">
<td>state</td>
<td><ul>
<li><p>absent</p></li>
<li><p>present</p></li>
</ul></td>
<td><p>Defines whether the port group must be present in the system.</p>
<ul>
<li><p>absent: The port group must not be present in the system.</p></li>
<li><p>present: The port group must be present in the system.</p></li>
</ul>
<p>This parameter is mandatory.</p></td>
</tr>
<tr class="odd">
<td>ports</td>
<td></td>
<td>Lists the port director and ports that are added to the port group or removed from port group.</td>
</tr>
<tr class="even">
<td>port_state</td>
<td><ul>
<li><p>present-in-group</p></li>
<li><p>absent-in-group</p></li>
</ul></td>
<td><p>Defines whether the port must be available in the port group.</p>
<p>● present-in-group: indicates that the port must be present in the port group.</p></td>
</tr>
</tbody>
</table>

### Table 8. Parameters (continued)

<table>
<thead>
<tr class="header">
<th><strong>Parameter</strong></th>
<th><strong>Choice/default</strong></th>
<th><strong>Comments</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td></td>
<td></td>
<td>● absent-in-group: indicates that the port must not be present in the port group.</td>
</tr>
<tr class="even">
<td>new_name</td>
<td></td>
<td><p>The new name of the port group when you rename the port group. The following conditions must be met when you enter a new name:</p>
<ul>
<li><p>Do not use special characters except "<em>_</em>."</p></li>
<li><p>Case sensitive for RestAPI calls.</p></li>
</ul></td>
</tr>
</tbody>
</table>

Masking View module
===================

  The Masking View module manages the masking views on the PowerMax
  array.
>
  The masking view module has the following functions:
>
  ● Create masking view with a port group, storage group, host, or host
  group. ● Modify masking view. ● Delete masking view.
>
  For creating a masking view, the port groups, storage groups, hosts,
  and host groups must be present on the array. Once the masking view is
  created, only the name of the masking view can be changed. The
  entities such as port group, storage group, hosts, or host group
  cannot be changed. The masking view can be created either for a host
  or a host group, but not for both. The host name or a host group name
  must be provided to create masking view.

Create masking view with host group
-----------------------------------

  The user can create a masking view with a host group by running the
  appropriate playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><p>- name: Create MV with hostgroup dellemc_powermax_maskingview: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}" mv_name: "{{mv_name}}"</p>
<p>portgroup_name: "Ansible_Testing_portgroup" hostgroup_name: "Ansible_Testing_hostgroup" sg_name: "Ansible_Testing_SG" state: "present"</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Create masking view with host
-----------------------------

  The user can create a masking view with host by running the
  appropriate playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Create MV with host

<table>
<tbody>
<tr class="odd">
<td><p>dellemc_powermax_maskingview: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}" mv_name: "{{mv_name}}"</p>
<p>portgroup_name: "Ansible_Testing_portgroup" host_name: "Ansible_Testing_host" sg_name: "Ansible_Testing_SG" state: "present"</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Rename masking view
-------------------

  The user can rename the masking view by running the appropriate
  playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><p>- name: Rename host masking view dellemc_powermax_maskingview: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}" mv_name: "{{mv_name}}"</p>
<p>new_mv_name: "Ansible_Testing_mv_renamed" state: "present"</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Delete masking view
-------------------

  The user can delete the masking view by running the appropriate
  playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><p>- name: Delete host masking view dellemc_powermax_maskingview: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}"</p>
<p>mv_name: "Ansible_Testing_mv_renamed" state: "absent"</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Masking View module parameters
------------------------------

  The parameters for the Masking View module are listed as follows with
  an example:

### Table 9. Parameters 

<table>
<thead>
<tr class="header">
<th><strong>Parameter</strong></th>
<th><strong>Choice/default</strong></th>
<th><strong>Comments</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>unispherehost</td>
<td></td>
<td>IP or FQDN of the Unisphere host. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>universion</td>
<td><ul>
<li><p>91</p></li>
<li><p>92</p></li>
</ul></td>
<td>The version of the Unisphere software. This parameter is optional.</td>
</tr>
<tr class="odd">
<td>verifycert</td>
<td>● True ● False</td>
<td><p>To validate the SSL certificate.</p>
<ul>
<li><p>True - Verifies the SSL certificate.</p></li>
<li><p>False - Specifies that the SSL certificate should not be verified.</p></li>
</ul>
<p>This parameter is mandatory.</p></td>
</tr>
<tr class="even">
<td>user</td>
<td></td>
<td>The user name to access the Unisphere server. The user name can be encrypted using Ansible vault. This parameter is mandatory.</td>
</tr>
<tr class="odd">
<td>password</td>
<td></td>
<td>The password to access the Unisphere server. The password can be encrypted using Ansible vault. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>serial_no</td>
<td></td>
<td>The serial number of the PowerMax array. If this parameter is absent, the script lists all the serial numbers of the registered array on the specified Unisphere host. This parameter is mandatory.</td>
</tr>
<tr class="odd">
<td>mv_name</td>
<td></td>
<td><p>The name of the masking view. The following conditions must be met when you enter the name:</p>
<ul>
<li><p>Do not use special characters except "<em>_</em>."</p></li>
<li><p>Case sensitive for RestAPI calls.</p></li>
</ul>
<p>This parameter is mandatory.</p></td>
</tr>
<tr class="even">
<td>new_mv_name</td>
<td></td>
<td><p>The new name of the masking view when you rename the existing masking view. The following conditions must be met when you provide the new name for masking view:</p>
<ul>
<li><p>Do not use special characters except "<em>_</em>."</p></li>
<li><p>Case sensitive for REST API calls.</p></li>
</ul></td>
</tr>
<tr class="odd">
<td>portgroup_name</td>
<td></td>
<td>The name of the existing port group.</td>
</tr>
<tr class="even">
<td>hostgroup_name</td>
<td></td>
<td>The name of the existing host group. Use this parameter to create cluster export.</td>
</tr>
<tr class="odd">
<td>host_name</td>
<td></td>
<td>The name of the existing host. Use this parameter to create an exclusive host or to export to a host.</td>
</tr>
</tbody>
</table>

### Table 9. Parameters (continued)

<table>
<thead>
<tr class="header">
<th><strong>Parameter</strong></th>
<th><strong>Choice/default</strong></th>
<th><strong>Comments</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>sg_name</td>
<td></td>
<td>The name of the existing storage group.</td>
</tr>
<tr class="even">
<td>state</td>
<td><ul>
<li><p>absent</p></li>
<li><p>present</p></li>
</ul></td>
<td>Defines whether the masking view must be present on the system. This parameter is mandatory.</td>
</tr>
</tbody>
</table>

Snapshot module
===============

  The Snapshot module manages the snapshots available on the PowerMax
  array.
>
  The snapshot module has the following functions:

-   Create a storage group snapshot.

-   Get details of a storage group snapshot.

-   Rename a storage group snapshot.

-   Change storage group snapshot link status.

-   Delete storage group snapshot.

Create snapshot for a storage group
-----------------------------------

  The user can create a snapshot for a storage group by running the
  appropriate playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><p>- name: Create a Snapshot for a Storage Group dellemc_powermax_snapshot: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}" sg_name: "ansible_sg"</p>
<p>snapshot_name: "ansible_sg_snap" ttl: "2" ttl_unit: "days" state: "present"</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Get details of storage group snapshot
-------------------------------------

  The user can get details of a storage group snapshot by running the
  appropriate playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Get Storage Group Snapshot details
  dellemc\_powermax\_snapshot: unispherehost: "{{unispherehost}}"
  universion: "{{universion}}" verifycert: "{{verifycert}}" user:
  "{{user}}" password: "{{password}}" serial\_no: "{{serial\_no}}"
  sg\_name: "ansible\_sg" snapshot\_name: "ansible\_sg\_snap" state:
  "present"
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Delete storage group snapshot
-----------------------------

  The user can delete a storage group snapshot by running the
  appropriate playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><p>- name: Delete Storage Group Snapshot dellemc_powermax_snapshot: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}" sg_name: "ansible_sg"</p>
<p>snapshot_name: "ansible_sg_snap" generation: 1 state: "absent"</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Rename storage group snapshot
-----------------------------

  The user can rename the storage group snapshot by running the
  appropriate playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><p>- name: Rename Storage Group Snapshot dellemc_powermax_snapshot: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}" sg_name: "ansible_sg"</p>
<p>snapshot_name: "ansible_sg_snap" new_snapshot_name: "ansible_snap_new" generation: 0 state: "present"</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Change snapshot link status to linked
-------------------------------------

  The user can change the link status of the snapshot to *linked* by
  running the appropriate playbook The syntax of the playbook is shown
  as follows:
>
  \- name: Change Snapshot Link Status to Linked
  dellemc\_powermax\_snapshot: unispherehost: "{{unispherehost}}"
  universion: "{{universion}}" verifycert: "{{verifycert}}" user:
  "{{user}}" password: "{{password}}" serial\_no: "{{serial\_no}}"
  sg\_name: "ansible\_sg"
>
  snapshot\_name: "ansible\_snap\_new" generation: 1
>
  target\_sg\_name: "ansible\_sg\_target" link\_status: "linked" state:
  "present"
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Change snapshot link status to unlinked
---------------------------------------

  The user can change the link status of the snapshot to *unlinked* by
  running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><p>- name: Change Snapshot Link Status to UnLinked dellemc_powermax_snapshot: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}" sg_name: "ansible_sg"</p>
<p>snapshot_name: "ansible_snap_new" generation: 1</p>
<p>target_sg_name: "ansible_sg_target" link_status: "unlinked" state: "present"</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Snapshot module parameters
--------------------------

  The parameters for the Snapshot module are listed as follows with an
  example:

### Table 10. Parameters 

<table>
<thead>
<tr class="header">
<th><strong>Parameter</strong></th>
<th><strong>Choice/default</strong></th>
<th><strong>Comments</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>unispherehost</td>
<td></td>
<td>IP or FQDN of the Unisphere host. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>universion</td>
<td><ul>
<li><p>91</p></li>
<li><p>92</p></li>
</ul></td>
<td>The version of the Unisphere software. This parameter is optional.</td>
</tr>
<tr class="odd">
<td>verifycert</td>
<td>● True ● False</td>
<td><p>To validate the SSL certificate.</p>
<ul>
<li><p>True - Verifies the SSL certificate.</p></li>
<li><p>False - Specifies that the SSL certificate should not be verified.</p></li>
</ul>
<p>This parameter is mandatory.</p></td>
</tr>
<tr class="even">
<td>user</td>
<td></td>
<td>The user name to access the Unisphere server. The user name can be encrypted using Ansible vault. This parameter is mandatory.</td>
</tr>
<tr class="odd">
<td>password</td>
<td></td>
<td>The password to access the Unisphere server. The password can be encrypted using Ansible vault. This parameter is mandatory.</td>
</tr>
</tbody>
</table>

### Table 10. Parameters (continued)

<table>
<thead>
<tr class="header">
<th><strong>Parameter</strong></th>
<th><strong>Choice/default</strong></th>
<th><strong>Comments</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>serial_no</td>
<td></td>
<td>The serial number of the PowerMax array. If this parameter is absent, the script lists all the serial numbers of the registered array on the specified Unisphere host. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>sg_name</td>
<td></td>
<td>The name of the storage group. This parameter is mandatory.</td>
</tr>
<tr class="odd">
<td>snapshot_name</td>
<td></td>
<td>The name of the snapshot. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>new_snapshot_name</td>
<td></td>
<td>The new name of the snapshot.</td>
</tr>
<tr class="odd">
<td>generation</td>
<td></td>
<td>The generation number of the Snapshot. Generation is mandatory for link, unlink, rename, and delete operations. Optional for <em>Get snapshot details</em  operation. Create snapshot creates a snapshot with generation number 0. Rename is supported only for generation number 0.</td>
</tr>
<tr class="even">
<td>target_sg_name</td>
<td></td>
<td>The target storage group name.</td>
</tr>
<tr class="odd">
<td>link_status</td>
<td><ul>
<li><p>linked</p></li>
<li><p>unlinked</p></li>
</ul></td>
<td>Defines the link status of the snapshot.</td>
</tr>
<tr class="even">
<td>ttl</td>
<td></td>
<td>The Time To Live (TTL) value for the Snapshot. If the TTL value is not specified, the storage group snapshot details would be returned. However, to create a storage group snapshot, the TTL must be specified. If the storage group snapshot does not have a TTL value, specify the TTL value as "None."</td>
</tr>
<tr class="odd">
<td>ttl_unit</td>
<td><ul>
<li><p>hours</p></li>
<li><p>days</p></li>
</ul></td>
<td>The unit for TTL. If no ttl_unit is specified, 'days' is taken as default value.</td>
</tr>
<tr class="even">
<td>state</td>
<td><ul>
<li><p>absent</p></li>
<li><p>present</p></li>
</ul></td>
<td>Defines whether the snapshot must exist on the storage array. This parameter is mandatory.</td>
</tr>
</tbody>
</table>

SRDF Module
===========

  The SRDF Module manages the SRDF links in Dell EMC PowerMax arrays.
  The SRDF Module supports the following functionalities:

-   Create SRDF links with the following replication modes:

    1.  Synchronous

  ○ Asynchronous
>
  ○ Adaptive copy
>
  ○ Active mode

-   Get SRDF pair states for a given storage group and RDFG number. ●
    Modify SRDF link mode.

-   Perform the following operations:

    1.  Establish

  ○ Restore
>
  ○ Swap
>
  ○ Failover
>
  ○ Resume
>
  ○ Suspend
>
  ○ Split
>
  ○ Failback
>
  ○ Setbias

-   Metro configurations: Set bias operation, change resiliency between
    bias and witness. ● Run create and update operations Asynchronously
    (by default) or synchronously.

-   Get Job details for a given Job ID.

-   Delete SRDF links.

-   Concurrent SRDF configuration support.

-   Online Device expansion support

  **NOTE:** The following features are not supported:

-   The Star and Cascaded SRDF configurations

-   The Invalidate, Ready, Not Ready, Move Pairs, and Refresh SRDF
    pairing operations

-   Migration use cases through the SRDF Module

Create SRDF links
-----------------

  The user can create SRDF links by running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><p>- name: Create and establish storagegroup SRDF/S pairing dellemc_powermax_srdf: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}"</p>
<p>remote_serial_no: "{{remote_serial_no}}" sg_name: "{{sg_name}}" srdf_mode: 'Synchronous' srdf_state: 'Establish' state: 'present'</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Create and establish a storage group SRDF/a pairing
---------------------------------------------------

  The user can create and establish a storage group SRDF/a pairing by
  running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><p>- name: Create and establish storagegroup SRDF/a pairing register: Job_details_body dellemc_powermax_srdf: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}" sg_name: "{{sg_name}}"</p>
<p>remote_serial_no: "{{remote_serial_no}}" srdf_mode: 'Asynchronous'</p></td>
</tr>
</tbody>
</table>

  srdf\_state: 'Establish' state: 'present'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Create a storage group SRDF/s pair in suspended mode
----------------------------------------------------

  The user can create a storage group SRDF/s pair in the default
  suspended mode by running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><p>- name: Create storagegroup SRDF/s pair in default suspended mode as an Synchronous task dellemc_powermax_srdf: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}" sg_name: "{{sg_name2}}"</p>
<p>remote_serial_no: "{{remote_serial_no}}" state: 'present' srdf_mode: 'Synchronous'</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Get SRDF details
----------------

  The user can get SRDF details by running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Get SRDF details dellemc\_powermax\_srdf: unispherehost:
  "{{unispherehost}}" universion: "{{universion}}" verifycert:
  "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial\_no:
  "{{serial\_no}}" sg\_name: "{{sg\_name}}" state: 'present'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Modify SRDF mode
----------------

  The user can modify SRDF mode by running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Modify SRDF mode dellemc\_powermax\_srdf: unispherehost:
  "{{unispherehost}}" universion: "{{universion}}" verifycert:
  "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial\_no:
  "{{serial\_no}}"
>
  sg\_name: "{{sg\_name}}" srdf\_mode: 'Synchronous' state: 'present'
>
  You can modify the srdf\_mode parameter to any of the following modes:

-   Synchronous

-   Asynchronous

-   Adaptive copy

-   Active

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Failover SRDF link
------------------

  The user can perform failover operation by running the appropriate
  playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Failover SRDF link dellemc\_powermax\_srdf: unispherehost:
  "{{unispherehost}}" universion: "{{universion}}" verifycert:
  "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial\_no:
  "{{serial\_no}}" sg\_name: "{{sg\_name}}" srdf\_state: 'Failover'
  state: 'present'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Failback SRDF link
------------------

  The user can perform failback operation by running the appropriate
  playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Failback SRDF link dellemc\_powermax\_srdf: unispherehost:
  "{{unispherehost}}" universion: "{{universion}}" verifycert:
  "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial\_no:
  "{{ serial\_no }}" sg\_name: "{{sg\_name}}“ rdfg\_no: "{{rdfg\_no}}"
  srdf\_state: "Failback" state: 'present'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Create storage group Metro SRDF pair with Witness for resiliency
----------------------------------------------------------------

  The user can create a storage group Metro SRDF pair with Witness for
  resiliency by running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><p>- name: Create storagegroup Metro SRDF pair with Witness for resiliency dellemc_powermax_srdf: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}" sg_name: "{{sg_name}}"</p>
<p>remote_serial_no: "{{remote_serial_no}}" state: 'present' srdf_mode: 'Active' srdf_state: 'Establish'</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Get SRDF Job status
-------------------

  The user can get SRDF Job status by running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Get SRDF Job status dellemc\_powermax\_srdf: unispherehost:
  "{{unispherehost}}" universion: "{{universion}}" verifycert:
  "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial\_no:
  "{{serial\_no}}" job\_id: "{{job\_id}}" state: 'present'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Establish SRDF link
-------------------

  The user can establish the SRDF link by running the appropriate
  playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Establish SRDF link dellemc\_powermax\_srdf: unispherehost:
  "{{unispherehost}}" universion: "{{universion}}" verifycert:
  "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial\_no:
  "{{serial\_no}}" sg\_name: "{{sg\_name}}" srdf\_state: 'Establish'
  state: 'present'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Create and Establish concurrent SRDF link
-----------------------------------------

  The user can establish the concurrent SRDF link (one at a time) by
  running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><ul>
<li><p>name: Create and Establish SRDF pairing with remote array 1 dellemc_powermax_srdf: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}"</p></li>
</ul>
<p>remote_serial_no: "{{remote_serial_no_1}}" sg_name: "{{sg_name}}" srdf_state: 'Establish' srdf_mode: 'Synchronous' state: 'present'</p>
<ul>
<li><p>name: Create and Establish SRDF pairing with remote array 2 dellemc_powermax_srdf: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: "{{serial_no}}"</p></li>
</ul>
<p>remote_serial_no: "{{remote_serial_no_2}}" sg_name: "{{sg_name}}" srdf_state: 'Establish' srdf_mode: 'Adaptive Copy' state: 'present'</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Suspend SRDF link
-----------------

  The user can suspend the SRDF link by running the appropriate
  playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Suspend SRDF link dellemc\_powermax\_srdf: unispherehost:
  "{{unispherehost}}" universion: "{{universion}}" verifycert:
  "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial\_no:
  "{{serial\_no}}" sg\_name: "{{sg\_name2}}" srdf\_state: 'Suspend'
  state: 'present'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Suspend concurrent SRDF link
----------------------------

  The user can suspend the concurrent SRDF link (one at a time) by
  running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Suspend SRDF link dellemc\_powermax\_srdf: unispherehost:
  "{{unispherehost}}" universion: "{{universion}}" verifycert:
  "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial\_no:
  "{{serial\_no}}" sg\_name: "{{sg\_name2}}" srdf\_state: 'Suspend'
  state: 'present'
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Delete SRDF link
----------------

  The user can delete the SRDF links by running the appropriate
  playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Delete SRDF link dellemc\_powermax\_srdf: unispherehost:
  "{{unispherehost}}" universion: "{{universion}}" verifycert:
  "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial\_no:
  "{{serial\_no}}" sg\_name: "{{sg\_name}}" state: 'absent'
>
  **NOTE:** Only links in Suspended states can be deleted.
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

Delete concurrent SRDF link
---------------------------

  The user can delete the concurrent SRDF link (one at a time) by
  running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:
>
  \- name: Delete SRDF link dellemc\_powermax\_srdf: unispherehost:
  "{{unispherehost}}" universion: "{{universion}}" verifycert:
  "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial\_no:
  "{{r1\_serial\_no}}" sg\_name: "{{sg\_name1}}" rdfg\_no:
  "{{rdfGroupNumber}}" state: 'absent' wait\_for\_completion: True
>
  **NOTE:** Only links in Suspended states can be deleted.
>
  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

SRDF module parameters
----------------------

The following table provides information about the parameters that are
displayed on the console, when the user runs the playbook using SRDF
Module: **Table 11. Parameters**

<table>
<thead>
<tr class="header">
<th><strong>Parameter</strong></th>
<th><strong>Choices/default</strong></th>
<th><strong>Comments</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>unispherehost</td>
<td></td>
<td>IP or FQDN of the Unisphere host. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>universion</td>
<td><ul>
<li><p>91</p></li>
<li><p>92</p></li>
</ul></td>
<td>The version of the Unisphere software. This parameter is optional.</td>
</tr>
<tr class="odd">
<td>verifycert</td>
<td>● True ● False</td>
<td><p>To validate the SSL certificate.</p>
<ul>
<li><p>True - indicates that the SSL certificate should be verified.</p></li>
<li><p>False - indicates that the SSL certificate should not be verified.</p></li>
</ul>
<p>This parameter is mandatory.</p></td>
</tr>
<tr class="even">
<td>user</td>
<td></td>
<td>The username to access the Unisphere server. The username can be encrypted using Ansible vault. This parameter is mandatory.</td>
</tr>
<tr class="odd">
<td>password</td>
<td></td>
<td>The password to access the Unisphere server. The password can be encrypted using Ansible vault. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>serial_no</td>
<td></td>
<td>The serial number of the source PowerMax or VMAX array (primary array), when protecting a storage group. This parameter is mandatory. <strong>NOTE:</strong  You can issue srdf_state operations from a primary or remote array.</td>
</tr>
<tr class="odd">
<td>remote_serial_no</td>
<td></td>
<td>A 12-Digit serial number of the remote PowerMAX or VMAX array (remote). This parameter is mandatory when creating an SRDF pair.</td>
</tr>
<tr class="even">
<td>sg_name</td>
<td></td>
<td><p>Name of the Storage group. SRDF pairings are managed at a storage group level. This parameter is required to identify the SRDF link.</p>
<p>This parameter is mandatory.</p></td>
</tr>
<tr class="odd">
<td>srdf_mode</td>
<td><ul>
<li><p>Active</p></li>
<li><p>Adaptive Copy</p></li>
<li><p>Synchronous</p></li>
<li><p>Asynchronous</p></li>
</ul></td>
<td><p>The replication mode of the SRDF pair. This parameter is mandatory when creating an SRDF pair. It can be modified by specifying one of the following values:</p>
<ul>
<li><p>Active</p></li>
<li><p>Adaptive Copy</p></li>
<li><p>Synchronous</p></li>
<li><p>Asynchronous</p></li>
</ul></td>
</tr>
<tr class="even">
<td>state</td>
<td>● present ● absent</td>
<td>Define whether the SRDF pairing should exist or not.</td>
</tr>
</tbody>
</table>

### Table 11. Parameters (continued)

<table>
<thead>
<tr class="header">
<th><strong>Parameter</strong></th>
<th><strong>Choices/default</strong></th>
<th><strong>Comments</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td></td>
<td></td>
<td><ul>
<li><p>present - indicate that the SRDF pairing should exist in the system.</p></li>
<li><p>absent - indicate that the SRDF pairing should not exist in the system.</p></li>
</ul>
<p>This parameter is mandatory.</p></td>
</tr>
<tr class="even">
<td>srdf_state</td>
<td><ul>
<li><p>Establish</p></li>
<li><p>Restore ● Swap</p></li>
<li><p>Failover</p></li>
<li><p>Resume</p></li>
<li><p>Suspend</p></li>
<li><p>Split</p></li>
<li><p>Failback</p></li>
<li><p>Setbias</p></li>
</ul></td>
<td>Desired state of the SRDF pairing. This parameter is optional. While creating a new SRDF pair, the allowed values are <strong>Establish</strong  and <strong>Suspend</strong>. If the srdf_state parameter is not specified, the pair will be created in the <strong>Suspend</strong  state.</td>
</tr>
<tr class="odd">
<td>new_rdf_group</td>
<td><ul>
<li><p>True</p></li>
<li><p>False</p></li>
</ul>
<p>The default value is false.</p></td>
<td>PowerMax has a limited number of RDF groups. If this flag is set to <em>True</em>, and the RDF groups are exhausted, then SRDF link creation will fail.</td>
</tr>
<tr class="even">
<td>rdfg_number</td>
<td></td>
<td>The RDF group number. This parameter is optional for each call. For the <strong>create</strong  operation, if specified, the array will reuse the RDF group, or display an error. For the <strong>modify</strong  and <strong>delete</strong  operations, if the RFD group number is not specified, the storage group is protected by multiple RDF Groups. This causes an error.</td>
</tr>
<tr class="odd">
<td>job_id</td>
<td></td>
<td>Job ID of an Asynchronous task. This parameter is used to get the details of a job.</td>
</tr>
<tr class="even">
<td>wait_for_completion</td>
<td><ul>
<li><p>True</p></li>
<li><p>False</p></li>
</ul>
<p>The default value is false.</p></td>
<td><p>Flag to indicate if the operation should be run synchronously or asynchronously.</p>
<ul>
<li><p>True - Synchronous</p></li>
<li><p>False - Asynchronously</p></li>
</ul>
<p>The default value is False. All create and update operations will be run asynchronously by default.</p></td>
</tr>
<tr class="odd">
<td>witness</td>
<td>● True ● False</td>
<td><p>Flag to specify use of Witness for a Metro configuration. The flag can be set only for modifying the srdf_state parameter to either Establish, Suspend or Restore.</p>
<ul>
<li><p>True - To use Witness</p></li>
<li><p>False - To use Bias</p></li>
</ul>
<blockquote>
<p><strong>NOTE:</strong  It is recommended to set this parameter for SRDF Metro in a production environment. Use <em>Unipshere for PowerMAX</em  UI or REST API to configure this parameter.</p>
<p><strong>NOTE:</strong  Set witness to <strong>true</strong  when you create a Metro configuration.</p>
</blockquote></td>
</tr>
</tbody>
</table>

RDF Group module
================

  The RDF Group module provides details of the RDF group and the list of
  volumes available on a specified RDF Group. The RDF group module
  supports the Get details of RDF Groups and volumes function.

Get RDF group and volumes details
---------------------------------

  The user can get details of an RDF group and the list of volumes in a
  specific RDF Group, by running the appropriate playbook.
>
  The syntax of the playbook is shown as follows:

<table>
<tbody>
<tr class="odd">
<td><p>- name: Get RDF Group detail and Volumes dellemc_powermax_rdfgroup: unispherehost: "{{unispherehost}}" universion: "{{universion}}" verifycert: "{{verifycert}}" user: "{{user}}" password: "{{password}}" serial_no: {{ serial_no }}</p>
<p>rdfgroup_number: "{{rdfgroup_number}}" register: "rdfgroup_result"</p></td>
</tr>
</tbody>
</table>

  The parameters must be set before the user runs the playbook. See the
  Parameters table for more information about the parameters.

RDF Group module parameters
---------------------------

  The parameters for the RDF Group module are listed as follows with an
  example:

### Table 12. Parameters 

<table>
<thead>
<tr class="header">
<th><strong>Parameter</strong></th>
<th><strong>Choice/default</strong></th>
<th><strong>Comments</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>unispherehost</td>
<td></td>
<td>IP or FQDN of the Unisphere host. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>universion</td>
<td><ul>
<li><p>91</p></li>
<li><p>92</p></li>
</ul></td>
<td>The version of the Unisphere software. This parameter is optional.</td>
</tr>
<tr class="odd">
<td>verifycert</td>
<td>● True ● False</td>
<td><p>To validate the SSL certificate.</p>
<ul>
<li><p>True - Verifies the SSL certificate.</p></li>
<li><p>False - Specifies that the SSL certificate should not be verified.</p></li>
</ul>
<p>This parameter is mandatory.</p></td>
</tr>
<tr class="even">
<td>user</td>
<td></td>
<td>The username to access the Unisphere server. The username can be encrypted using Ansible vault. This parameter is mandatory.</td>
</tr>
<tr class="odd">
<td>password</td>
<td></td>
<td>The password to access the Unisphere server. The password can be encrypted using Ansible vault. This parameter is mandatory.</td>
</tr>
<tr class="even">
<td>serial_no</td>
<td></td>
<td>The serial number of the PowerMax array. If this parameter is absent, the script lists all the serial numbers of the registered array on the specified Unisphere host. This parameter is mandatory.</td>
</tr>
</tbody>
</table>

### Table 12. Parameters (continued)

| **Parameter**    | **Choice/default** | **Comments**                                                                                                                 |
|------------------|--------------------|------------------------------------------------------------------------------------------------------------------------------|
| rdfgroup\_number |                    | The serial number of the RDF Group, used to get the details of an RDF Group and list the volumes of the specified RDF Group. |
