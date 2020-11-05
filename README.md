# **Ansible Modules for Dell EMC PowerMax**

## **Product Guide**

**1.2**

![](RackMultipart20201029-4-4mjey4_html_64d14239b5dc073.png)

**September 2020**

Notes, cautions, and warnings

![](RackMultipart20201029-4-4mjey4_html_ccc782b327b61821.png) ![](RackMultipart20201029-4-4mjey4_html_e7ec2e65d5a2ee65.png) **NOTE:** A NOTE indicates important information that helps you make better use of your product.

![](RackMultipart20201029-4-4mjey4_html_6a6be0fee6fa9ea7.png) ![](RackMultipart20201029-4-4mjey4_html_7f58a03cf5cb64a7.png)

![](RackMultipart20201029-4-4mjey4_html_851a6d9e17e1993f.png) **CAUTION:**  **A CAUTION indicates either potential damage to hardware or loss of data and tells you how to avoid**** the problem.**

![](RackMultipart20201029-4-4mjey4_html_1ad5e80b439ffd46.png) ![](RackMultipart20201029-4-4mjey4_html_62a380bb6d7bf662.png) **WARNING:**  **A WARNING indicates a potential for property damage, personal injury, or death.**

![](RackMultipart20201029-4-4mjey4_html_e028c50feb4f0228.png)

© 2016 - 2020 Dell Inc. or its subsidiaries. All rights reserved. Dell, EMC, and other trademarks are trademarks of Dell Inc. or its subsidiaries.

Other trademarks may be trademarks of their respective owners.

![](RackMultipart20201029-4-4mjey4_html_28a581717820be1e.gif)
# **1**

# **Introduction**

This chapter contains the following topics:

**Topics:**

- [Product overview](#page3)

## **Product overview**

The Ansible Modules for Dell EMC PowerMax are used to automate and orchestrate the configuration, and deployment of the Dell EMC PowerMax arrays. The capabilities of Ansible modules are managing volumes, storage groups, ports, port groups, hosts, host groups, masking views, snapshots, SRDF pairings and state, gather high level facts about the arrays and RDF group configuration. The options available for each capability are list, show, create, delete, and modify.

The Ansible modules are called by tasks within the Ansible playbooks. The _Idempotency_ feature is enabled for all the modules.

The _Idempotency_ feature enables the playbook to be run multiple times and hence supports fault tolerance. The modules use

Unisphere RESTAPI to interface with the PowerMax arrays.

List of Ansible Modules for Dell EMC PowerMax

The following are the list of modules:

- [Gather facts module](#page6)

- [Storage group module](#page12)

- [Volume module](#page18)

- [Host module](#page24)

- [Host group module](#page29)

- [Port module](#page33)

- [Port group module](#page34)

- [Masking view module](#page38)

- [Snapshot module](#page41)

- [SRDF module](#page44)

- [RDF Group module](#page53)

**Introduction**** 3**

![](RackMultipart20201029-4-4mjey4_html_28a581717820be1e.gif)
# **2**

# **Configure Ansible**

This chapter contains the following topics:

**Topics:**

- [Software prerequisites](#page4)

- [Set up the Ansible host](#page4)

## **Software prerequisites**

This table provides information about the software prerequisites for the Ansible Modules for Dell EMC PowerMax.

Prerequisites

**Table 1. Software prerequisites**

| **Ansible** |
 | **Unisphere** |
 | **PowerMaxOS** |
 | **Red Hat** |
 | **Python** |
 | **Python library** |
 | **Ansible** |
 |
 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| **Modules** |
 | **Version** |
 |
 |
 | **Enterprise Linux** |
 | **version** |
 | **version** |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
| v1.0 |
 | 9.0 |
 | 5978.221.221 |
 | 7.5 |
 | 2.7.12 |
 |
 | 3.0.0.14 |
 | 2.6 or later |
 |
 |
|
 |
 |
 |
 | 5978.444.444 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
| v1.1 |
 | 9.0 |
 | 5978.221.221 |
 | 7.5 |
 | 2.7.12 |
 |
 | 3.1.x |
 | 2.6 or later |
 |
 |
|
 |
 | 9.1 |
 | 5978.444.444 |
 |
 |
 | 3.5.2 |
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
| v1.2 |
 | 9.1 and above |
 | 5978.221.221 |
 | 7.5 |
 | 2.7 or later |
 | 9.1.0.0 and above |
 | 2.8 or later |
 |
 |
|
 |
 |
 |
 | 5978.444.444 |
 | 7.6, 7.7, 7.8, and |
 |
 |
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 | 5978.665.665 |
 | 8.2 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |

![](RackMultipart20201029-4-4mjey4_html_b7ff6de4a2d731b0.png)

![](RackMultipart20201029-4-4mjey4_html_a33b98122cbbb61a.png) **NOTE:** Unisphere Version 9.1 is compatible with PowerMax Python library version 9.1.x.x. Similarly, Unisphere version above9.1 only works with Python library version greater than 9.1.x.x.

![](RackMultipart20201029-4-4mjey4_html_9f619c1d7101a758.png) ![](RackMultipart20201029-4-4mjey4_html_7f58a03cf5cb64a7.png)

## **Set up the Ansible host**

The Ansible server must be configured to write and run Ansible playbooks.

**About this task**

Do the following before you run playbooks on Ansible modules for Dell EMC PowerMax:

**Steps**

1. Install Python library for Unisphere.

Run the following command to install PyU4V:

![](RackMultipart20201029-4-4mjey4_html_1d9c89ddb1a95773.gif)

sudo apt install python-pip

pip install PyU4V

For more information, see [PyU4V Documentation](https://pyu4v.readthedocs.io/en/latest/).

**4**** Configure Ansible**

1. Create the dellemc folder in one of the following folders if it is not available:

- For Python 2.7 /usr/lib/python2.7/site-packages/ansible/modules/storage

- For Python 3.5 /usr/lib/python3.5/site-packages/ansible/modules/storage

1. Create the dell folder in one of the following folders if it is not available:

- For Python 2.7 /usr/lib/python2.7/site-packages/ansible/module\_utils/storage

- For Python 3.5 /usr/lib/python3.5/site-packages/ansible/module\_utils/storage

1. Copy the Ansible modules to the appropriate locations in the virtual machine.

1. Copy _dellemc\_ansible\_powermax\_utils.py_ and _\_init\_.py_ from the /utils to one of the following locations:

- For Python 2.7 /usr/lib/python2.7/site-packages/ansible/module\_utils/storage/dell

- For Python 3.5 /usr/lib/python3.5/site-packages/ansible/module\_utils/storage/dell

1. Copy all the module python files from the /library folder to one of the following:

- For Python 2.7 /usr/lib/python2.7/site-packages/ansible/modules/storage/dellemc

- For Python 3.5 /usr/lib/python3.5/site-packages/ansible/modules/storage/dellemc/

1. Copy the _dellemc\_powermax.py_ from /doc\_fragments to one of the following:

- For Python 2.7 /usr/lib/python2.7/site-packages/ansible/plugins/doc\_fragments

- For Python 3.5 /usr/lib/python3.5/site-packages/ansible/plugins/doc\_fragments/

![](RackMultipart20201029-4-4mjey4_html_4bea6ff619d36d05.png) ![](RackMultipart20201029-4-4mjey4_html_e7ec2e65d5a2ee65.png) **NOTE:** The path may vary depending on the Python library version and the operating system.

![](RackMultipart20201029-4-4mjey4_html_7f58a03cf5cb64a7.png)

**Configure Ansible**** 5**

![](RackMultipart20201029-4-4mjey4_html_28a581717820be1e.gif)
# **3**

# **Ansible modules for Dell EMC PowerMax**

This chapter presents the following topics:

**Topics:**

- [Gather Facts module](#page6)

- [Storage group module](#page12)

- [Volume module](#page18)

- [Host module](#page24)

- [Host group module](#page29)

- [Port module](#page33)

- [Port Group module](#page34)

- [Masking View module](#page38)

- [Snapshot module](#page41)

- [SRDF Module](#page44)

- [RDF Group module](#page53)

## **Gather Facts module**

The Gather Facts module displays a list of specific entities in PowerMax array. The Gather facts module is used with Ansible to register values that are used in conditional statements within the playbooks.

The Gather Facts module supports two sets of operations.

- Operations on the Unisphere server

- Operations on the PowerMax array registered under an Unisphere server

On the Unisphere host, the Gather Facts module lists the registered storage arrays that are managed by the Unisphere host.

On the PowerMax array, the Gather Facts module lists the following entities:

- Arrays in an Unisphere host

- Volumes in a specific array

- Storage groups in a specific array

- Hosts in a specific array

- Host groups in a specific array

- Storage resource pools in a specific array

- Ports in a specific array

- Port groups in a specific array

- Masking views in a specific array

- RDF groups in a specific array

- Health status of the array

- Support for generic filters for PowerMax array entities

**Get list of volumes**

The user can get the list of volumes and TDEV volumes in the storage array by running the appropriate playbook.

The syntax of the playbook is as follows:

![](RackMultipart20201029-4-4mjey4_html_52411522692c4f4d.gif)

- name: Get list of volumes dellemc\_powermax\_gatherfacts:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

**6**** Ansible modules for Dell EMC PowerMax**

verifycert: &quot;{{verifycert}}&quot;

![](RackMultipart20201029-4-4mjey4_html_8187d329035c8d34.gif)

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

tdev\_volumes: &quot;True&quot;

gather\_subset:

- vol

The parameters must be set before the user runs the playbook. See the [Parameters table](#page11)for more information about the parameters.

**Get list of arrays**

The user can get the list of registered storage arrays that are managed by the Unisphere host by running the appropriate playbook.

The syntax for the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_69dd0d109ce283af.gif)

- name: Get array list

dellemc\_powermax\_gatherfacts: unispherehost: &quot;{{unispherehost}}&quot; universion: &quot;{{universion}}&quot; verifycert: &quot;{{verifycert}}&quot; user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page11)for more information about the parameters.

**Get list of storage group**

The user can get the list of storage groups in the array by running the appropriate playbook.

The syntax for the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_7284e4285e2de4ab.gif)

- name: Get list of Storage groups dellemc\_powermax\_gatherfacts:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot; gather\_subset:

  - sg

The parameters must be set before the user runs the playbook. See the [Parameters table](#page11)for more information about the parameters.

**Get list of storage resource pool**

The user can get the list of storage resource pools, and the details of each storage resource pool in the array by running the appropriate playbook.

The syntax for the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_3391369f06718de2.gif)

- name: Get list of Storage Resource Pools dellemc\_powermax\_gatherfacts:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

**Ansible modules for Dell EMC PowerMax**** 7**

serial\_no: &quot;{{serial\_no}}&quot;

![](RackMultipart20201029-4-4mjey4_html_be4fc28e6ef0bfc0.gif)

gather\_subset:

- srp

The parameters must be set before the user runs the playbook. See the [Parameters table](#page11)for more information about the parameters.

**Get list of port groups**

The user can get the list of port groups in the array by running the appropriate playbook.

The syntax for the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_7284e4285e2de4ab.gif)

- name: Get list of Port Groups dellemc\_powermax\_gatherfacts:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot; gather\_subset:

  - pg

The parameters must be set before the user runs the playbook. See the [Parameters table](#page11)for more information about the parameters.

**Get list of hosts**

The user can get the list of hosts in the array by running the appropriate playbook.

The syntax for the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_7284e4285e2de4ab.gif)

- name: Get list of Hosts dellemc\_powermax\_gatherfacts:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot; gather\_subset:

  - host

The parameters must be set before the user runs the playbook. See the [Parameters table](#page11)for more information about the parameters.

**Get list of host groups**

The user can get the list of host groups in the array by running the appropriate playbook.

The syntax for the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_3e8be906193b9c44.gif)

- name: Get list of Host Groups dellemc\_powermax\_gatherfacts:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

**8**** Ansible modules for Dell EMC PowerMax**

gather\_subset:

![](RackMultipart20201029-4-4mjey4_html_680ac7189a708599.gif)

- hg

The parameters must be set before the user runs the playbook. See the [Parameters table](#page11)for more information about the parameters.

**Get list of ports**

The user can get the list of ports in the array by running the appropriate playbook.

The syntax for the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_7284e4285e2de4ab.gif)

- name: Get list of Ports dellemc\_powermax\_gatherfacts:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot; gather\_subset:

  - port

The parameters must be set before the user runs the playbook. See the [Parameters table](#page11)for more information about the parameters.

**Get list of masking views**

The user can get the list of masking views available in the storage array by running the appropriate playbook.

The syntax for the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_7284e4285e2de4ab.gif)

- name: Get list of Maskng Views dellemc\_powermax\_gatherfacts:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot; gather\_subset:

  - mv

The parameters must be set before the user runs the playbook. See the [Parameters table](#page11)for more information about the parameters.

**Get list of RDF groups**

The user can get the list of RDF groups in the array by running the appropriate playbook.

The syntax for the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_bcb60680fdfdeadd.gif)

- name: Get list of all RDF Groups of given PowerMax/VMAX Storage System dellemc\_powermax\_gatherfacts:

unispherehost: &quot;{{unispherehost}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

gather\_subset:

- rdf

register: subset\_result

**Ansible modules for Dell EMC PowerMax**** 9**

- debug:

![](RackMultipart20201029-4-4mjey4_html_680ac7189a708599.gif)

var: subset\_result

The parameters must be set before the user runs the playbook. See the [Parameters table](#page11)for more information about the parameters.

**Get array health status**

The user can get the health status of the storage arrays that are managed by the Unisphere host by running the appropriate playbook.

The syntax of the playbook is as follows:

![](RackMultipart20201029-4-4mjey4_html_7284e4285e2de4ab.gif)

- name: Get array health status dellemc\_powermax\_gatherfacts:

unispherehost: &quot;{{unispherehost}}

&quot;universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot; gather\_subset:

  - health

The parameters must be set before the user runs the playbook. See the [Parameters table](#page11)for more information about the parameters.

**Get list of volumes and storage groups with filter**

The user can get the list of volumes and storage groups, with appropriate filter, in the arrays that are managed by the Unisphere host by running the appropriate playbook.

The syntax of the playbook is as follows:

![](RackMultipart20201029-4-4mjey4_html_8c50d60243f2f546.gif)

- name: Get list of volumes and storage groups with filter dellemc\_powermax\_gatherfacts:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot; gather\_subset:

  - vol
  - sg

filters:

- filter\_key: &quot;tdev&quot;

filter\_operator: &quot;equal&quot;

filter\_value: &quot;True&quot;

- filter\_key: &quot;cap\_gb&quot;

filter\_operator: &quot;equal&quot;

filter\_value: &quot;5&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page11)for more information about the parameters.

**10**** Ansible modules for Dell EMC PowerMax**

**Gather Facts module parameters**

The following table provides the information about the parameters that are displayed on the console, when the user runs the _playbook_ using the Gather facts module:

**Table 2. Parameters**

|
 | **Parameter** |
 | **Choices/default** |
 | **Comments** |
 |
 |
 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
|
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
|
 | unispherehost |
 |
 |
 |
 | IP or FQDN of the Unisphere host. This |
 |
 |
 |
|
 |
 |
 |
 |
 |
 | parameter is mandatory. |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
|
 | universion |
 | ? | 91 |
 | The version of the Unisphere software. |
 |
 |
 |
|
 |
 |
 | ? | 92 |
 | This parameter is optional. |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
|
 | verifycert |
 | ? | True |
 | To validate the SSL certificate. |
 |
 |
 |
|
 |
 |
 | ? | False |
 | ? True - Verify the SSL certificate. |
 |
 |
 |
|
 |
 |
 |
 |
 |
 | ? False - Do not verify the SSL |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 | certificate. |
 |
 |
 |
|
 |
 |
 |
 |
 |
 | This parameter is mandatory. |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
|
 | user |
 |
 |
 |
 | The user name to access the Unisphere |
 |
 |
 |
|
 |
 |
 |
 |
 |
 | server. The user name can be encrypted |
 |
 |
 |
|
 |
 |
 |
 |
 |
 | using Ansible vault. This parameter is |
 |
 |
 |
|
 |
 |
 |
 |
 |
 | mandatory. |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
|
 | password |
 |
 |
 |
 | The password to access the Unisphere |
 |
 |
 |
|
 |
 |
 |
 |
 |
 | server. The password can be encrypted |
 |
 |
 |
|
 |
 |
 |
 |
 |
 | using Ansible vault. This parameter is |
 |
 |
 |
|
 |
 |
 |
 |
 |
 | mandatory. |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
|
 | serial\_no |
 |
 |
 |
 | The serial number of the PowerMax |
 |
 |
 |
|
 |
 |
 |
 |
 |
 | array. If this parameter is absent, the |
 |
 |
 |
|
 |
 |
 |
 |
 |
 | script lists all the serial numbers of the |
 |
 |
 |
|
 |
 |
 |
 |
 |
 | registered array on the specified |
 |
 |
 |
|
 |
 |
 |
 |
 |
 | Unisphere host. This parameter is |
 |
 |
 |
|
 |
 |
 |
 |
 |
 | optional. |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
|
 | gather\_subset |
 | ? | vol |
 | List of string variables to specify the |
 |
 |
 |
|
 |
 |
 | ? | srp |
 | PowerMax entities for which the |
 |
 |
 |
|
 |
 |
 |
 | information is required. Required only if |
 |
 |
 |
|
 |
 |
 | ? | sg |
 |
 |
 |
 |
|
 |
 |
 |
 | serial\_no is present. |
 |
 |
 |
|
 |
 |
 | ? | pg |
 |
 |
 |
 |
|
 |
 |
 |
 | ? | vol - volumes |
 |
 |
 |
|
 |
 |
 | ? | host |
 |
 |
 |
 |
|
 |
 |
 | ? | hg |
 | ? | srp - storage resource pools |
 |
 |
 |
|
 |
 |
 | ? | port |
 | ? | sg - storage groups |
 |
 |
 |
|
 |
 |
 | ? | mv |
 | ? | pg - port groups |
 |
 |
 |
|
 |
 |
 | ? | rdf |
 | ? | host - hosts |
 |
 |
 |
|
 |
 |
 | ? | health |
 | ? | hg - host groups |
 |
 |
 |
|
 |
 |
 |
 |
 |
 | ? | port - ports |
 |
 |
 |
|
 |
 |
 |
 |
 |
 | ? mv - masking views |
 |
 |
 |
|
 |
 |
 |
 |
 |
 | ? rdf - RDF groups |
 |
 |
 |
|
 |
 |
 |
 |
 |
 | ? health - health status of a specific |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 | PowerMax array |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
|
 | tdev\_volumes |
 | ? | True |
 | This parameter supports a boolean |
 |
 |
 |
|
 |
 |
 | ? | False |
 | variable. By setting the value of this |
 |
 |
 |
|
 |
 |
 |
 |
 |
 | parameter to _True_, only TDEV Volumes |
 |
 |
 |
|
 |
 |
 |
 |
 |
 | will be listed. The default value of this |
 |
 |
 |
|
 |
 |
 |
 |
 |
 | parameter is _True_. |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
 |
|
 | filters |
 |
 |
 |
 |
 |
 |
 |
 |
 |

![](RackMultipart20201029-4-4mjey4_html_7fba1b5f40b9d10e.png)

filter\_key

Name identifier of the filter.

**Ansible modules for Dell EMC PowerMax**** 11**

**Table 2. Parameters (continued)**

![](RackMultipart20201029-4-4mjey4_html_71dfde8492fba241.png)

**Parameter**

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png) ![](RackMultipart20201029-4-4mjey4_html_d129f813cef34cc.png) ![](RackMultipart20201029-4-4mjey4_html_c4eeded2bb456dd.png)

filter\_operator

![](RackMultipart20201029-4-4mjey4_html_34ee038612f8d708.png)

filter\_value

**Choices/default**

![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_d129f813cef34cc.png) ![](RackMultipart20201029-4-4mjey4_html_c4eeded2bb456dd.png)

- equal

- greater

- lesser

- like

![](RackMultipart20201029-4-4mjey4_html_7b230ced9d012c21.png)

**Comments**

![](RackMultipart20201029-4-4mjey4_html_a5c4074af46c76e8.png)

![](RackMultipart20201029-4-4mjey4_html_6ddab17d6739316f.png) **NOTE:** Filters are applicable onlywhen it is a valid filter \_key, else the SDK will ignore it and return the usual result.

![](RackMultipart20201029-4-4mjey4_html_df19a13595d7f13c.png)

If a valid filter\_key is passed and the given condition does not match, then an empty list is generated in the output.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

Operation to be performed on filter key.

![](RackMultipart20201029-4-4mjey4_html_672a140957bed290.png)

Value of the filter key.

![](RackMultipart20201029-4-4mjey4_html_5ad7bf5aeddf85f5.png) **NOTE:** When thefilter\_ valueisgiven as _True_ or _False_, then the filter\_operator is ignoredirrespective of its value, because the SDK treats the value as bool type.

filters:

- filter\_key: tdev filter\_operator: equal filter\_value: True

## **Storage group module**

The Storage group module manages the storage groups available on the PowerMax storage array.

The storage group module has the following functionalities:

- List the volumes of a storage group.

- Create a storage group.

- Delete an existing storage group.

- Add existing volumes to a storage group.

- Remove existing volumes from a storage group.

- Create volumes in a storage group.

- Modify the storage group attributes.

- Add child storage group to a parent storage group.

- Remove child storage group from a parent storage group.

- Add new volumes to SRDF protected storage group.

- Remove volumes from SRDF protected storage group.

**Get details of storage group including the volumes**

The user can get the details of a storage group in the array. The details include the list of volumes within the storage group.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_384a7874a1c4dcf2.gif)

- name: Get storage group details including volumes dellemc\_powermax\_storagegroup:

unispherehost: &quot;{{unispherehost}}&quot;

**12**** Ansible modules for Dell EMC PowerMax**

universion: &quot;{{universion}}&quot;

![](RackMultipart20201029-4-4mjey4_html_8187d329035c8d34.gif)

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;ansible\_sg&quot;

state: &quot;present&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page17)for more information about the parameters.

**Create empty storage group**

The user can create an empty storage group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_1c3b622f4d628e4d.gif)

- name: Create empty storage group dellemc\_powermax\_storagegroup:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;foo&quot;

service\_level: &quot;Diamond&quot;

srp: &quot;SRP\_1&quot;

compression: True

state: &quot;present&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page17)for more information about the parameters.

**Delete empty storage group**

The user can delete an empty storage group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_7284e4285e2de4ab.gif)

- name: Delete the storage Group dellemc\_powermax\_storagegroup:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;foo&quot;

state: &quot;absent&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page17)for more information about the parameters.

**Add existing volumes to the existing storage group**

The user can add one or more existing volumes to a storage group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_384a7874a1c4dcf2.gif)

- name: Adding existing volume(s) to existing SG dellemc\_powermax\_storagegroup:

unispherehost: &quot;{{unispherehost}}&quot;

**Ansible modules for Dell EMC PowerMax**** 13**

universion: &quot;{{universion}}&quot;

![](RackMultipart20201029-4-4mjey4_html_bcb60680fdfdeadd.gif)

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;foo&quot;

state: &quot;present&quot;

volumes:

- vol\_id: &quot;00028&quot;
- vol\_id: &quot;00018&quot;
- vol\_id: &quot;00025&quot;

vol\_state: &quot;present-in-group&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page17)for more information about the parameters.

**Add new volumes to SRDF protected storage group**

The user can add volumes to a SRDF protected storage group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_3b832ac1238a07b0.gif)

- name: Add volumes to SRDF protected storage group dellemc\_powermax\_storagegroup:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;{{sg\_name}}&quot;

state: &quot;present&quot; volumes:

  - vol\_name: &quot;{{vol\_name1}}&quot;

size: 1

cap\_unit: &quot;GB&quot;

  - vol\_name: &quot;{{vol\_name2}}&quot;

size: 1

cap\_unit: &quot;GB&quot;

vol\_state: &quot;present-in-group&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page17)for more information about the parameters.

![](RackMultipart20201029-4-4mjey4_html_b7ff6de4a2d731b0.png)

![](RackMultipart20201029-4-4mjey4_html_a33b98122cbbb61a.png) **NOTE:** Add volumes to SRDF protected storage group is supported from PowerMax foxtail\_version (v5978.444.444)onwards.

![](RackMultipart20201029-4-4mjey4_html_9f619c1d7101a758.png) ![](RackMultipart20201029-4-4mjey4_html_7f58a03cf5cb64a7.png)

**Create new volumes for existing storage group**

The user can create new volumes for an existing storage group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_58c4dbbcff6772ae.gif)

- name: Create new volumes for existing SG dellemc\_powermax\_storagegroup:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;foo&quot;

state: &quot;present&quot; volumes:

  - vol\_name: &quot;foo&quot;

size: 1

**14**** Ansible modules for Dell EMC PowerMax**

cap\_unit: &quot;GB&quot;

![](RackMultipart20201029-4-4mjey4_html_52411522692c4f4d.gif)

- vol\_name: &quot;bar&quot;

size: 1

cap\_unit: &quot;GB&quot;

vol\_state: &quot;present-in-group&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page17)for more information about the parameters.

**Remove volumes from storage group**

The user can remove one or multiple volumes from a storage group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_45bf54edf81991f5.gif)

- name: Remove volume(s) from existing SG dellemc\_powermax\_storagegroup:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;foo&quot;

state: &quot;present&quot; volumes:

  - vol\_id: &quot;00028&quot;
  - vol\_id: &quot;00018&quot;
  - vol\_name: &quot;ansible-vol&quot;

vol\_state: &quot;absent-in-group&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page17)for more information about the parameters.

**Remove volumes from SRDF protected storage group**

The user can remove multiple volumes from a SRDF protected storage group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_ddfcea7564e4e812.gif)

- name: Remove volumes from SRDF protected storage group dellemc\_powermax\_storagegroup:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;{{sg\_name}}&quot;

state: &quot;present&quot; volumes:

  - vol\_name: &quot;{{vol\_name1}}&quot;
  - vol\_name: &quot;{{vol\_name2}}&quot;

vol\_state: &quot;absent-in-group&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page17)for more information about the parameters.

**Ansible modules for Dell EMC PowerMax**** 15**

**Add child storage group to parent storage group**

The user can add a child storage group to a parent storage group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_ddfcea7564e4e812.gif)

- name: Adding child SG to parent SG dellemc\_powermax\_storagegroup:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;parent\_sg&quot;

state: &quot;present&quot; child\_storage\_groups:

  - &quot;pie&quot;
  - &quot;bar&quot;

child\_sg\_state: &quot;present-in-group&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page17)for more information about the parameters.

**Remove child storage group from parent storage group**

The user can remove a child storage group from a parent storage group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_ddfcea7564e4e812.gif)

- name: Removing child SG from parent SG dellemc\_powermax\_storagegroup:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;parent\_sg&quot;:

state: &quot;present&quot; child\_storage\_groups:

  - &quot;pie&quot;
  - &quot;bar&quot;

child\_sg\_state: &quot;absent-in-group&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page17)for more information about the parameters.

**Rename storage group**

The user can rename a storage group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_aacaf59cfea37794.gif)

- name: Rename Storage Group dellemc\_powermax\_storagegroup:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;ansible\_sg&quot;:

**16**** Ansible modules for Dell EMC PowerMax**

new\_sg\_name: &quot;ansible\_sg\_renamed&quot;

![](RackMultipart20201029-4-4mjey4_html_680ac7189a708599.gif)

state: &quot;present&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page17)for more information about the parameters.

**Storage Group module parameters**

The following table lists the parameters that must be set before the user runs the playbook for the Storage Group module:

**Table 3. Parameters**

![](RackMultipart20201029-4-4mjey4_html_71dfde8492fba241.png)

**Parameter**

![](RackMultipart20201029-4-4mjey4_html_d129f813cef34cc.png) ![](RackMultipart20201029-4-4mjey4_html_c4eeded2bb456dd.png)

unispherehost

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

universion

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

verifycert

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

user

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

password

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

serial\_no

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

sg\_name

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

new\_sg\_name

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

service\_level

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

srp

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

compression

![](RackMultipart20201029-4-4mjey4_html_d5c77acd64d8e1e5.png)

state

**Choices/default**

![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_d129f813cef34cc.png) ![](RackMultipart20201029-4-4mjey4_html_c4eeded2bb456dd.png)

- 91

- 92

- True

- False

![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png)

- true

- false

The default value is true.

![](RackMultipart20201029-4-4mjey4_html_810686020a82da65.png)

- absent

- present

**Comments**

![](RackMultipart20201029-4-4mjey4_html_d129f813cef34cc.png) ![](RackMultipart20201029-4-4mjey4_html_c4eeded2bb456dd.png)

IP or FQDN of the Unisphere host. This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The version of the Unisphere software.

This parameter is optional.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

To validate the SSL certificate.

- True - Verifies the SSL certificate.

- False - Specifies that the SSL certificate should not be verified.

This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The user name to access the Unisphere server. The user name can be encrypted using Ansible vault. This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The password to access the Unisphere server. The password can be encrypted using Ansible vault. This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The serial number of the PowerMax array. If this parameter is absent, the script lists all the serial numbers of the registered array on the specified Unisphere host. This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The name of the storage group. This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The new name of the storage group.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The name of the service level

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The name of the storage resource pool. This parameter is ignored if the service\_level is not specified. Thedefault value is the name of the default storage resource pool of the array.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

Defines if the compression is enable for a storage group. This parameter is unavailable if the service\_level is not specified.

![](RackMultipart20201029-4-4mjey4_html_41a2f1d4c4331.png)

Defines whether the storage group should exist or not. This parameter is mandatory.

**Ansible modules for Dell EMC PowerMax**** 17**

**Table 3. Parameters (continued)**

| **Parameter** |
 | **Choices/default** |
 | **Comments** |
 |
 |
| --- | --- | --- | --- | --- | --- | --- |
|
 |
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
 |
| volumes |
 |
 |
 |
 | This parameter lists the volumes present |
 |
 |
|
 |
 |
 |
 |
 | in the storage group. Each volume has |
 |
 |
|
 |
 |
 |
 |
 | four attributes. |
 |
 |
|
 |
 |
 |
 |
 | ? | vol\_name |
 |
 |
|
 |
 |
 |
 |
 | ? | size |
 |
 |
|
 |
 |
 |
 |
 | ? | cap\_unit |
 |
 |
|
 |
 |
 |
 |
 | ? | vol\_id |
 |
 |
|
 |
 |
 |
 |
 | Use either volume name or volume ID to |
 |
 |
|
 |
 |
 |
 |
 | identify the volumes. Both cannot be |
 |
 |
|
 |
 |
 |
 |
 | used simultaneously to identify the |
 |
 |
|
 |
 |
 |
 |
 | volumes. For new volumes that are |
 |
 |
|
 |
 |
 |
 |
 | added to storage group, the name and |
 |
 |
|
 |
 |
 |
 |
 | size must be provided. This parameter is |
 |
 |
|
 |
 |
 |
 |
 | optional. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| vol\_state |
 | ? | present-in-group |
 | Defines the state of the volumes inside |
 |
 |
|
 |
 | ? | absent-in-group |
 | the storage group. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| child\_storage\_groups |
 |
 |
 |
 | Lists the child storage group. |
 |
 |
| child\_sg\_state |
 | ? | present-in-group |
 | Describes the state of child storage |
 |
 |
|
 |
 | ? | absent-in-group |
 | group in a parent storage group. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
 |

## **Volume module**

The Volume module manages the storage volumes on PowerMax arrays.

The volume module has the following capabilities:

- Create volume.

- Expand volume.

- Rename volume.

- Delete volume using the volume ID.

- Move volumes between storage groups.

- Get volume details.

The volume module has the following capabilities using WWN:

- Expand volume.

- Rename volume.

- Delete volume using the volume ID.

- Move volumes between storage groups.

- Get volume details.

- Add new volume to SRDF protected storage group.

- Expand volume which is part of SRDF protected storage group.

**Create volume**

The user can create a volume in the storage group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_180cfa22d92f6147.gif)

- name: Create volume dellemc\_powermax\_volume:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

**18**** Ansible modules for Dell EMC PowerMax**

user: &quot;{{user}}&quot;

![](RackMultipart20201029-4-4mjey4_html_3391369f06718de2.gif)

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

vol\_name: &quot;{{vol\_name}}&quot;

sg\_name: &quot;{{sg\_name}}&quot;

size: 1

cap\_unit: &quot;{{cap\_unit}}&quot;

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page23)for more information about the parameters.

**Expand volume**

The user can expand the size of the volumes by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_b8ead8090c2b170f.gif)

- name: Expand volume size dellemc\_powermax\_volume:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

size: 3

cap\_unit: &quot;{{cap\_unit}}&quot;

vol\_id: &quot;0059B&quot;

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page23)for more information about the parameters.

**Rename volume**

The user can rename the volume by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_80462f446880980b.gif)

- name: Rename volume dellemc\_powermax\_volume:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

new\_name: &quot;{{new\_vol\_name}}&quot;

vol\_id: &quot;0059B&quot;

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page23)for more information about the parameters.

**Delete volume**

The user can delete the volume by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_be4fc28e6ef0bfc0.gif)

- name: Delete volume dellemc\_powermax\_volume:

**Ansible modules for Dell EMC PowerMax**** 19**

unispherehost: &quot;{{unispherehost}}&quot;

![](RackMultipart20201029-4-4mjey4_html_3391369f06718de2.gif)

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

vol\_id: &quot;0059B&quot;

state: &#39;absent&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page23)for more information about the parameters.

**Move volumes between storage group**

The user can move the volumes from one storage group to another by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_b8ead8090c2b170f.gif)

- name: Move volume between storage group dellemc\_powermax\_volume:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

vol\_name: &quot;{{vol\_name}}&quot;

sg\_name: &quot;{{sg\_name}}&quot;

new\_sg\_name: &quot;{{new\_sg\_name}}&quot;

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page23)for more information about the parameters.

**Add new volume to SRDF protected storage group**

The user can add a volume to the SRDF protected storage group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_1c3b622f4d628e4d.gif)

- name: Add new volume to SRDF protected storage group dellemc\_powermax\_volume:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

vol\_name: &quot;{{vol\_name}}&quot;

sg\_name: &quot;{{sg\_name}}&quot;

size: 1

cap\_unit: &quot;{{cap\_unit}}&quot;

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page23)for more information about the parameters.

![](RackMultipart20201029-4-4mjey4_html_b7ff6de4a2d731b0.png)

![](RackMultipart20201029-4-4mjey4_html_b2348532066adb1b.png) **NOTE:** Add volume to SRDF protected storage group is supported from PowerMax foxtail\_version (v5978.444.444)onwards.

![](RackMultipart20201029-4-4mjey4_html_9f619c1d7101a758.png) ![](RackMultipart20201029-4-4mjey4_html_7f58a03cf5cb64a7.png)

**20**** Ansible modules for Dell EMC PowerMax**

**Expand volume of SRDF protected storage group using volume name**

The user can expand volume of SRDF protected storage group using volume name by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_1c3b622f4d628e4d.gif)

- name: Expand volume of SRDF protected storage group using volume name dellemc\_powermax\_volume:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

vol\_name: &quot;{{vol\_name}}&quot;

sg\_name: &quot;{{sg\_name}}&quot;

size: 8

cap\_unit: &quot;{{cap\_unit}}&quot;

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page23)for more information about the parameters.

![](RackMultipart20201029-4-4mjey4_html_b7ff6de4a2d731b0.png)

![](RackMultipart20201029-4-4mjey4_html_a33b98122cbbb61a.png) **NOTE:** Expand volume of SRDF protected storage group using volume name is supported from PowerMax foxtail\_version(v5978.444.444) onwards.

![](RackMultipart20201029-4-4mjey4_html_9f619c1d7101a758.png) ![](RackMultipart20201029-4-4mjey4_html_7f58a03cf5cb64a7.png)

**Expand volume of SRDF protected storage group using volume identifier**

The user can expand volume of SRDF protected storage group using identifier by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_b8ead8090c2b170f.gif)

- name: Expand volume of SRDF protected storage group using volume identifier dellemc\_powermax\_volume:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

vol\_id: &quot;{{vol\_id}}&quot;

size: 8

cap\_unit: &quot;{{cap\_unit}}&quot;

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page23)for more information about the parameters.

![](RackMultipart20201029-4-4mjey4_html_b7ff6de4a2d731b0.png)

![](RackMultipart20201029-4-4mjey4_html_a33b98122cbbb61a.png) **NOTE:** Expand volume of SRDF protected storage group using volume identifier is supported from PowerMaxfoxtail\_version (v5978.444.444) onwards.

![](RackMultipart20201029-4-4mjey4_html_9f619c1d7101a758.png) ![](RackMultipart20201029-4-4mjey4_html_7f58a03cf5cb64a7.png)

**Get volume using WWN**

The user can get details of a volume using WWN by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_52411522692c4f4d.gif)

- name: Get volume details dellemc\_powermax\_volume:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

**Ansible modules for Dell EMC PowerMax**** 21**

verifycert: &quot;{{verifycert}}&quot;

![](RackMultipart20201029-4-4mjey4_html_180cfa22d92f6147.gif)

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

vol\_wwn: &quot;{{result.volume\_details.wwn}}&quot;

state: &quot;present&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page23)for more information about the parameters.

**Expand volume using WWN**

The user can expand the size of the volumes using WWN by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_b8ead8090c2b170f.gif)

- name: Expand volume using wwn dellemc\_powermax\_volume:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

size: 21

cap\_unit: &quot;{{cap\_unit}}&quot;

vol\_wwn: &quot;{{result.volume\_details.wwn}}&quot;

state: &quot;present&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page23)for more information about the parameters.

**Move volumes between storage groups using WWN**

The user can move the volumes using WWN, from one storage group to another by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_b8ead8090c2b170f.gif)

- name: Move volume between Storage group dellemc\_powermax\_volume:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

vol\_wwn: &quot;{{result.volume\_details.wwn}}&quot;

sg\_name: &quot;{{sg\_name}}&quot;

new\_sg\_name: &quot;{{new\_sg\_name}}&quot;

state: &quot;present&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page23)for more information about the parameters.

**Rename volume using WWN**

The user can rename the volume using WWN by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_384a7874a1c4dcf2.gif)

- name: Rename volume dellemc\_powermax\_volume:

unispherehost: &quot;{{unispherehost}}&quot;

**22**** Ansible modules for Dell EMC PowerMax**

universion: &quot;{{universion}}&quot;

![](RackMultipart20201029-4-4mjey4_html_3391369f06718de2.gif)

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

new\_name: &quot;Ansible\_Testing\_Renamed&quot;

vol\_wwn: &quot;{{result.volume\_details.wwn}}&quot;

state: &quot;present&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page23)for more information about the parameters.

**Delete volume using WWN**

The user can delete the volume using WWN by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_7284e4285e2de4ab.gif)

- name: Delete volume dellemc\_powermax\_volume:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

vol\_wwn: &quot;{{result.volume\_details.wwn}}&quot;

state: &quot;absent&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page23)for more information about the parameters.

**Volume module parameters**

The parameters of the Volume module are listed as follows:

**Table 4. Parameters**

| **Parameter** |
 | **Choices/default** |
 | **Comments** |
 |
 |
| --- | --- | --- | --- | --- | --- | --- |
|
 |
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| unispherehost |
 |
 |
 |
 | IP or FQDN of the Unisphere host. This |
 |
 |
|
 |
 |
 |
 |
 | parameter is mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| universion |
 | ? | 91 |
 | The version of the Unisphere software. |
 |
 |
|
 |
 | ? | 92 |
 | This parameter is optional. |
 |
 |
|
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| verifycert |
 | ? | True |
 | To validate the SSL certificate. |
 |
 |
|
 |
 | ? | False |
 | ? True - Verifies the SSL certificate. |
 |
 |
|
 |
 |
 |
 |
 | ? False - Specifies that the SSL |
 |
 |
|
 |
 |
 |
 |
 | certificate should not be verified. |
 |
 |
|
 |
 |
 |
 |
 | This parameter is mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| user |
 |
 |
 |
 | The user name to access the Unisphere |
 |
 |
|
 |
 |
 |
 |
 | server. The user name can be encrypted |
 |
 |
|
 |
 |
 |
 |
 | using Ansible vault. This parameter is |
 |
 |
|
 |
 |
 |
 |
 | mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| password |
 |
 |
 |
 | The password to access the Unisphere |
 |
 |
|
 |
 |
 |
 |
 | server. The password can be encrypted |
 |
 |
|
 |
 |
 |
 |
 | using Ansible vault. This parameter is |
 |
 |
|
 |
 |
 |
 |
 | mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| serial\_no |
 |
 |
 |
 | The serial number of the PowerMax |
 |
 |
|
 |
 |
 |
 |
 | array. If this parameter is absent, the |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |

**Ansible modules for Dell EMC PowerMax**** 23**

**Table 4. Parameters (continued)**

| **Parameter** |
 | **Choices/default** |
 | **Comments** |
 |
 |
| --- | --- | --- | --- | --- | --- | --- |
|
 |
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 | script lists all the serial numbers of the |
 |
 |
|
 |
 |
 |
 |
 | registered array on the specified |
 |
 |
|
 |
 |
 |
 |
 | Unisphere host. This parameter is |
 |
 |
|
 |
 |
 |
 |
 | mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| vol\_name |
 |
 |
 |
 | The name of the volume. |
 |
 |
| new\_name |
 |
 |
 |
 | The new identifier for the volume. |
 |
 |
| sg\_name |
 |
 |
 |
 | The name of the current storage group. |
 |
 |
| new\_sg\_name |
 |
 |
 |
 | The name of the target storage group |
 |
 |
|
 |
 |
 |
 |
 | for moving volumes from one storage |
 |
 |
|
 |
 |
 |
 |
 | group to another. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| size |
 |
 |
 |
 | The desired size of the volume. This |
 |
 |
|
 |
 |
 |
 |
 | parameter is mandatory when you create |
 |
 |
|
 |
 |
 |
 |
 | or expand the volume. Shrinking of |
 |
 |
|
 |
 |
 |
 |
 | volumes is not supported. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| cap\_unit |
 | ? | MB |
 | Volume capacity unit. |
 |
 |
|
 |
 | ? | GB |
 |
 |
 |
 |
|
 |
 | ? | TB |
 |
 |
 |
 |
|
 |
 | The default unit is _GB_. |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| vol\_id |
 |
 |
 |
 | The native id of the volume. This |
 |
 |
|
 |
 |
 |
 |
 | parameter is optional. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| state |
 | ? | absent |
 | Defines whether the volume should exist |
 |
 |
|
 |
 | ? | present |
 | in the storage group. This parameter is |
 |
 |
|
 |
 |
 | mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| vol\_wwn |
 |
 |
 |
 | The external WWN of the volume. This |
 |
 |
|
 |
 |
 |
 |
 | parameter is optional. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |

## **Host module**

The host module manages the host within the PowerMax array.

The host module has the following functions:

- Create host with initiators and host flags.

- Add initiators to the host.

- Remove initiators from the host.

- Modify host flag values.

- Rename host.

- Delete host.

**Create host**

The user can create a host by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_3391369f06718de2.gif)

- name: Create host dellemc\_powermax\_host:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

**24**** Ansible modules for Dell EMC PowerMax**

serial\_no: &quot;{{serial\_no}}&quot;

![](RackMultipart20201029-4-4mjey4_html_bcb60680fdfdeadd.gif)

host\_name: &quot;{{host\_name}}&quot;

initiators:

- 10000090fa7b4e85 host\_flags:

spc2\_protocol\_version: true

consistent\_lun: true

volume\_set\_addressing: &#39;unset&#39;

disable\_q\_reset\_on\_ua: false

openvms: &#39;unset&#39; state: &#39;present&#39; initiator\_state: &#39;present-in-host&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page27)for more information about the parameters.

**Get details of the host**

The user can get details of the host by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_7284e4285e2de4ab.gif)

-name: Get host details

dellemc\_powermax\_host:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

host\_name: &quot;{{host\_name}}&quot;

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page27)for more information about the parameters.

**Add initiator to host**

The user can add an initiator to the host by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_1c3b622f4d628e4d.gif)

- name: Adding initiator to host dellemc\_powermax\_host:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

host\_name: &quot;{{host\_name}}&quot; initiators:

- 10000090fa3d303e

initiator\_state: &#39;present-in-host&#39;

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page27)for more information about the parameters.

**Ansible modules for Dell EMC PowerMax**** 25**

**Remove initiators from host**

The user can remove initiators from the host by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_1c3b622f4d628e4d.gif)

- name: Removing initiator from host dellemc\_powermax\_host:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

host\_name: &quot;{{host\_name}}&quot;

initiators:

- 10000090fa3d303e

initiator\_state: &#39;absent-in-host&#39;

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page27)for more information about the parameters.

**Modify host flags**

The user can modify the host flags by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_472786df4bf65b41.gif)

- name: Modify flags of host

dellemc\_powermax\_host: unispherehost: &quot;{{unispherehost}}&quot; universion: &quot;{{universion}}&quot; verifycert: &quot;{{verifycert}}&quot; user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

host\_name: &quot;{{host\_name}}&quot; host\_flags:

spc2\_protocol\_version: unset

consistent\_lun: unset

volume\_set\_addressing: true

disable\_q\_reset\_on\_ua: false

openvms: false

avoid\_reset\_broadcast: true state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page27)for more information about the parameters.

**Rename host**

The user can rename the host by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_3e8be906193b9c44.gif)

- name: Rename host dellemc\_powermax\_host:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

**26**** Ansible modules for Dell EMC PowerMax**

host\_name: &quot;{{host\_name}}&quot;

![](RackMultipart20201029-4-4mjey4_html_be4fc28e6ef0bfc0.gif)

new\_name: &quot;{{new\_host\_name}}&quot;

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page31)for more information about the parameters.

**Delete host**

The user can delete the host by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_7284e4285e2de4ab.gif)

- name: Delete host dellemc\_powermax\_host:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

host\_name: &quot;{{new\_host\_name}}&quot;

state: &#39;absent&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page31)for more information about the parameters.

**Host module parameters**

The parameters of the Host module are listed as follows:

**Table 5. Parameters**

| **Parameter** |
 | **Choice/default** |
 | **Comments** |
 |
 |
| --- | --- | --- | --- | --- | --- | --- |
|
 |
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| unispherehost |
 |
 |
 |
 | IP or FQDN of the Unisphere host. This |
 |
 |
|
 |
 |
 |
 |
 | parameter is mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| universion |
 | ? | 91 |
 | The version of the Unisphere software. |
 |
 |
|
 |
 | ? | 92 |
 | This parameter is optional. |
 |
 |
|
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| verifycert |
 | ? | True |
 | To validate the SSL certificate. |
 |
 |
|
 |
 | ? | False |
 | ? True - Verifies the SSL certificate. |
 |
 |
|
 |
 |
 |
 |
 | ? False - Specifies that the SSL |
 |
 |
|
 |
 |
 |
 |
 | certificate should not be verified. |
 |
 |
|
 |
 |
 |
 |
 | This parameter is mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| user |
 |
 |
 |
 | The user name to access the Unisphere |
 |
 |
|
 |
 |
 |
 |
 | server. The user name can be encrypted |
 |
 |
|
 |
 |
 |
 |
 | using Ansible vault. This parameter is |
 |
 |
|
 |
 |
 |
 |
 | mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| password |
 |
 |
 |
 | The password to access the Unisphere |
 |
 |
|
 |
 |
 |
 |
 | server. The password can be encrypted |
 |
 |
|
 |
 |
 |
 |
 | using Ansible vault. This parameter is |
 |
 |
|
 |
 |
 |
 |
 | mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| serial\_no |
 |
 |
 |
 | The serial number of the PowerMax |
 |
 |
|
 |
 |
 |
 |
 | array. If this parameter is absent, the |
 |
 |
|
 |
 |
 |
 |
 | script lists all the serial numbers of the |
 |
 |
|
 |
 |
 |
 |
 | registered array on the specified |
 |
 |
|
 |
 |
 |
 |
 | Unisphere host. This parameter is |
 |
 |
|
 |
 |
 |
 |
 | mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |

**Ansible modules for Dell EMC PowerMax**** 27**

**Table 5. Parameters (continued)**

![](RackMultipart20201029-4-4mjey4_html_71dfde8492fba241.png)

**Parameter**

![](RackMultipart20201029-4-4mjey4_html_d129f813cef34cc.png) ![](RackMultipart20201029-4-4mjey4_html_c4eeded2bb456dd.png)

host\_name

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

new\_name

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

initiators

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

host\_flags

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

state

![](RackMultipart20201029-4-4mjey4_html_290c15fc400e26b0.png)

initiator\_state

**Choice/default**

![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_d129f813cef34cc.png) ![](RackMultipart20201029-4-4mjey4_html_c4eeded2bb456dd.png)

- yes

- no

- unset

The default parameter is _unset_.

![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png)

- absent

- present

- present-in-host

- absent-in-host

![](RackMultipart20201029-4-4mjey4_html_4b7b0a82a687bfa6.png)

**Comments**

![](RackMultipart20201029-4-4mjey4_html_d129f813cef34cc.png) ![](RackMultipart20201029-4-4mjey4_html_c4eeded2bb456dd.png)

The name of the host. The following conditions are applicable when naming the host:

- Do not use special characters except &quot;_\__.&quot;

- Case sensitive for RestAPI calls.

This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The new name of the host when you rename the host. The following conditions must be met when you enter a new name:

- Do not use special characters except &quot;_\__.&quot;

- Case sensitive for RestAPI calls.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

Lists the initiator _WWN_ or _IQN_ that needs to be added to or removed from the host.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

Enter as in _yaml_ dictionary. The host\_flags are optional. All the host\_flags are listed below.

- volume\_set\_addressing

- disable\_q\_reset\_on\_ua

- environ\_set

- avoid\_reset\_broadcast

- openvms

- scsi\_3

- spc2\_protocol\_version

- scsi\_support1

- consistent\_lun

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

Defines whether the host must exist in the system.

- absent - indicates that the host must not exist in the system.

- present - indicates that the host must exist in the system.

This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_12b5bc3ab9be3539.png)

Defines whether the initiator must be available in the host.

- present-in-host - indicates that the initiator must be present in the host.

- absent-in-host - indicates that the initiator must not be present in the host.

This parameter is mandatory for the following conditions:

- Create a host with initiators.

- Add initiators to a host.

- Remove initiators from a host

**28**** Ansible modules for Dell EMC PowerMax**

## **Host group module**

The host group module manages the host group within the PowerMax array. A host group is a container for multiple hosts and enables simple configuration of clusters.

The functions of the host group module are as follows:

- Create host group with hosts.

- Add hosts to a host group.

- Remove hosts from a host group.

- Rename host group.

- Modify the host flags of a host group.

- Delete host group.

**Create host group**

The user can create a host group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_8c50d60243f2f546.gif)

- name: Create host group

dellemc\_powermax\_hostgroup:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

hostgroup\_name: &quot;{{hostgroup\_name}}&quot;

hosts:

- Ansible\_Testing\_host state: &#39;present&#39; host\_state: &#39;present-in-group&#39; host\_flags:

spc2\_protocol\_version: true

consistent\_lun: true

disable\_q\_reset\_on\_ua: false

openvms: &#39;unset&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page31)for more information about the parameters.

**Get details of host group**

The user can get the details of the host group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_7284e4285e2de4ab.gif)

- name: Get host group details dellemc\_powermax\_hostgroup:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

hostgroup\_name: &quot;{{hostgroup\_name}}&quot;

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page31)for more information about the parameters.

**Ansible modules for Dell EMC PowerMax**** 29**

**Add host to host group**

The user can add host to a host group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_1c3b622f4d628e4d.gif)

- name: Adding host to host group dellemc\_powermax\_hostgroup:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

hostgroup\_name: &quot;{{hostgroup\_name}}&quot;

hosts:

- Ansible\_Testing\_host2 state: &#39;present&#39; host\_state: &#39;present-in-group&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page31)for more information about the parameters.

**Remove host from host group**

The user can remove a host from the host group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_1c3b622f4d628e4d.gif)

- name: Removing host from host group

dellemc\_powermax\_hostgroup:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

hostgroup\_name: &quot;{{hostgroup\_name}}&quot;

hosts:

- Ansible\_Testing\_host2 state: &#39;present&#39; host\_state: &#39;absent-in-group&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page31)for more information about the parameters.

**Modify host group flags**

The user can modify the host flags by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_71a836b7a09a9962.gif)

- name: Modify flags of host group dellemc\_powermax\_hostgroup:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

hostgroup\_name: &quot;{{hostgroup\_name}}&quot; host\_flags:

spc2\_protocol\_version: unset

disable\_q\_reset\_on\_ua: false

**30**** Ansible modules for Dell EMC PowerMax**

openvms: false

![](RackMultipart20201029-4-4mjey4_html_be4fc28e6ef0bfc0.gif)

avoid\_reset\_broadcast: true

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page31)for more information about the parameters.

**Rename host group**

The user can rename the host group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_80462f446880980b.gif)

- name: Rename host group dellemc\_powermax\_hostgroup:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

hostgroup\_name: &quot;{{hostgroup\_name}}&quot;

new\_name: &quot;Ansible\_Testing\_hostgroup2&quot;

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page31)for more information about the parameters.

**Delete host group**

The user can delete the host group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_7284e4285e2de4ab.gif)

- name: Delete host group dellemc\_powermax\_hostgroup:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

hostgroup\_name: &quot;Ansible\_Testing\_hostgroup2&quot;

state: &#39;absent&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page31)for more information about the parameters.

**Host Group module parameters**

The parameters of the Host Group module are listed as follows with an example:

**Table 6. Parameters**

| **Parameter** |
 | **Choice/default** |
 | **Comments** |
 |
 |
| --- | --- | --- | --- | --- | --- | --- |
|
 |
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| unispherehost |
 |
 |
 |
 | IP or FQDN of the Unisphere host. This |
 |
 |
|
 |
 |
 |
 |
 | parameter is mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| universion |
 | ? | 91 |
 | The version of the Unisphere software. |
 |
 |
|
 |
 | ? | 92 |
 | This parameter is optional. |
 |
 |
|
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |

**Ansible modules for Dell EMC PowerMax**** 31**

**Table 6. Parameters (continued)**

![](RackMultipart20201029-4-4mjey4_html_71dfde8492fba241.png)

**Parameter**

![](RackMultipart20201029-4-4mjey4_html_d129f813cef34cc.png) ![](RackMultipart20201029-4-4mjey4_html_c4eeded2bb456dd.png)

verifycert

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

user

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

password

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

serial\_no

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

host\_group\_name

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

new\_name

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

hosts

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

host\_state

![](RackMultipart20201029-4-4mjey4_html_18abc3a15794bc80.png)

host\_flags

**Choice/default**

![](RackMultipart20201029-4-4mjey4_html_d129f813cef34cc.png) ![](RackMultipart20201029-4-4mjey4_html_c4eeded2bb456dd.png)

- True

- False

![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png)

- present-in-group

- absent-in-group

![](RackMultipart20201029-4-4mjey4_html_a8effba2322802e2.png)

- yes

- no

- unset (default)

**Comments**

![](RackMultipart20201029-4-4mjey4_html_d129f813cef34cc.png) ![](RackMultipart20201029-4-4mjey4_html_c4eeded2bb456dd.png)

To validate the SSL certificate.

- True - Verifies the SSL certificate.

- False - Specifies that the SSL certificate should not be verified.

This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The user name to access the Unisphere server. The user name can be encrypted using Ansible vault. This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The password to access the Unisphere server. The password can be encrypted using Ansible vault. This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The serial number of the PowerMax array. If this parameter is absent, the script lists all the serial numbers of the registered array on the specified Unisphere host. This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The name of the host group. The following conditions must be met when you enter the name:

- Do not use special characters except &quot;_\__.&quot;

- Case sensitive for RestAPI calls.

This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The new name of the host group when you rename the host group. The following conditions must be met when you enter a new name:

- Do not use special characters except &quot;_\__.&quot;

- Case sensitive for RestAPI calls.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

Lists of the host names that are added to the host group or removed from host group. You can create an empty host group.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

Defines whether the host must be available in the host group.

- present-in-group - indicates that the host must be present in the host group.

- absent-in-group - indicates that the host must not be present in the host group.

![](RackMultipart20201029-4-4mjey4_html_a714a3be6c6c9594.png)

Enter as in _yaml_ dictionary. All the host\_flags are listed below.

- volume\_set\_addressing

- disable\_q\_reset\_on\_ua

- environ\_set

**32**** Ansible modules for Dell EMC PowerMax**

**Table 6. Parameters (continued)**

| **Parameter** |
 | **Choice/default** |
 | **Comments** |
 |
 |
| --- | --- | --- | --- | --- | --- | --- |
|
 |
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 | ? avoid\_reset\_broadcast |
 |
 |
|
 |
 |
 |
 |
 | ? | openvms |
 |
 |
|
 |
 |
 |
 |
 | ? | scsi\_3 |
 |
 |
|
 |
 |
 |
 |
 | ? spc2\_protocol\_version |
 |
 |
|
 |
 |
 |
 |
 | ? | scsi\_support1 |
 |
 |
|
 |
 |
 |
 |
 | ? | consistent\_lun |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| state |
 | ? | absent |
 | Defines whether the host group must be |
 |
 |
|
 |
 | ? | present |
 | present in the system. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 | ? absent - The host must not be |
 |
 |
|
 |
 |
 |
 |
 |
 | present in the system. |
 |
 |
|
 |
 |
 |
 |
 | ? present - The host must be present |
 |
 |
|
 |
 |
 |
 |
 |
 | in the system. |
 |
 |
|
 |
 |
 |
 |
 | This parameter is mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
 |

## **Port module**

The ports available on the PowerMax array are managed by the Port module. The Port module lists the details of single or multiple ports.

**Get details of single/multiple ports**

The user can get the details of single or multiple ports by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_1c3b622f4d628e4d.gif)

- name: Get details of single/multiple ports dellemc\_powermax\_port:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{array\_id}}&quot; ports:

  - director\_id: &quot;FA-1D&quot;

port\_id: &quot;5&quot;

  - director\_id: &quot;SE-1F&quot;

port\_id: &quot;29&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page33)for more information about the parameters.

**Port module parameters**

The parameters for the Port module are listed as follows with an example:

**Table 7. Parameters**

| **Parameter** |
 | **Choice/default** |
 | **Comments** |
 |
 |
| --- | --- | --- | --- | --- | --- | --- |
|
 |
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| unispherehost |
 |
 |
 |
 | IP or FQDN of the Unisphere host. This |
 |
 |
|
 |
 |
 |
 |
 | parameter is mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| universion |
 | ? | 91 |
 | The version of the Unisphere software. |
 |
 |
|
 |
 | ? | 92 |
 | This parameter is optional. |
 |
 |
|
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |

**Ansible modules for Dell EMC PowerMax**** 33**

**Table 7. Parameters (continued)**

| **Parameter** |
 | **Choice/default** |
 | **Comments** |
 |
| --- | --- | --- | --- | --- | --- |
|
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
| verifycert |
 | ? | True |
 | To validate the SSL certificate. |
 |
|
 |
 | ? | False |
 | ? True - Verifies the SSL certificate. |
 |
|
 |
 |
 |
 |
 | ? False - Specifies that the SSL |
 |
|
 |
 |
 |
 |
 | certificate should not be verified. |
 |
|
 |
 |
 |
 |
 | This parameter is mandatory. |
 |
|
 |
 |
 |
 |
 |
 |
 |
| user |
 |
 |
 |
 | The user name to access the Unisphere |
 |
|
 |
 |
 |
 |
 | server. The user name can be encrypted |
 |
|
 |
 |
 |
 |
 | using Ansible vault. This parameter is |
 |
|
 |
 |
 |
 |
 | mandatory. |
 |
|
 |
 |
 |
 |
 |
 |
 |
| password |
 |
 |
 |
 | The password to access the Unisphere |
 |
|
 |
 |
 |
 |
 | server. The password can be encrypted |
 |
|
 |
 |
 |
 |
 | using Ansible vault. This parameter is |
 |
|
 |
 |
 |
 |
 | mandatory. |
 |
|
 |
 |
 |
 |
 |
 |
 |
| serial\_no |
 |
 |
 |
 | The serial number of the PowerMax |
 |
|
 |
 |
 |
 |
 | array. If this parameter is absent, the |
 |
|
 |
 |
 |
 |
 | script lists all the serial numbers of the |
 |
|
 |
 |
 |
 |
 | registered array on the specified |
 |
|
 |
 |
 |
 |
 | Unisphere host. This parameter is |
 |
|
 |
 |
 |
 |
 | mandatory. |
 |
|
 |
 |
 |
 |
 |
 |
 |
| ports |
 |
 |
 |
 | Lists the port director and the port id. |
 |

## **Port Group module**

The Port Group module manages the port group in the PowerMax array.

The port group management module has the following functions:

- Create a port group with ports.

- Create empty port group.

- Add ports to a port group.

- Remove ports from a port group.

- Rename a port group.

- Remove a port group.

**Create port group without ports**

The user can create a port group without ports by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_7284e4285e2de4ab.gif)

- name: Create port group without ports dellemc\_powermax\_portgroup:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{array\_id}}&quot;

portgroup\_name: &quot;{{portgroup\_name}}&quot;

state: &quot;present&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page37)for more information about the parameters.

**34**** Ansible modules for Dell EMC PowerMax**

**Create port group with ports**

The user can create a port group with ports by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_451e5659773eccd0.gif)

- name: Create port group with ports dellemc\_powermax\_portgroup:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{array\_id}}&quot;

portgroup\_name: &quot;{{portgroup\_name}}&quot;

state: &quot;present&quot; ports:

  - director\_id: &quot;FA-1D&quot;

port\_id: &quot;5&quot;

  - director\_id: &quot;FA-2D&quot;

port\_id: &quot;5&quot;

port\_state: &quot;present-in-group&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page37)for more information about the parameters.

**Add ports to port group**

The user can add ports to a port group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_451e5659773eccd0.gif)

- name: Add ports to port group dellemc\_powermax\_portgroup:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{array\_id}}&quot;

portgroup\_name: &quot;{{portgroup\_name}}&quot;

state: &quot;present&quot; ports:

  - director\_id: &quot;FA-2D&quot;

port\_id: &quot;8&quot;

  - director\_id: &quot;FA-2D&quot;

port\_id: &quot;9&quot;

port\_state: &quot;present-in-group&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page37)for more information about the parameters.

**Remove ports from port group**

The user can remove ports from the port group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_8187d329035c8d34.gif)

- name: Remove ports from port group dellemc\_powermax\_portgroup:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

**Ansible modules for Dell EMC PowerMax**** 35**

password: &quot;{{password}}&quot;

![](RackMultipart20201029-4-4mjey4_html_aacaf59cfea37794.gif)

serial\_no: &quot;{{array\_id}}&quot;

portgroup\_name: &quot;{{portgroup\_name}}&quot;

state: &quot;present&quot;

ports:

- director\_id: &quot;FA-2D&quot; port\_id: &quot;8&quot;
- director\_id: &quot;FA-2D&quot; port\_id: &quot;9&quot;

port\_state: &quot;absent-in-group&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page37)for more information about the parameters.

**Rename port group**

The user can rename the port group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_80462f446880980b.gif)

- name: Modify port group dellemc\_powermax\_portgroup:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{array\_id}}&quot;

portgroup\_name: &quot;{{portgroup\_name}}&quot;

state: &quot;present&quot;

new\_name: &quot;{{new\_name}}&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page37)for more information about the parameters.

**Delete port group**

The user can delete a port group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_7284e4285e2de4ab.gif)

- name: Delete port group dellemc\_powermax\_portgroup:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{array\_id}}&quot;

portgroup\_name: &quot;{{portgroup\_name}}&quot;

state: &quot;absent&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page37)for more information about the parameters.

**36**** Ansible modules for Dell EMC PowerMax**

**Port Group module parameters**

The parameters for the Port Group module are listed as follows with an example:

**Table 8. Parameters**

![](RackMultipart20201029-4-4mjey4_html_71dfde8492fba241.png)

**Parameter**

![](RackMultipart20201029-4-4mjey4_html_d129f813cef34cc.png) ![](RackMultipart20201029-4-4mjey4_html_c4eeded2bb456dd.png)

unispherehost

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

universion

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

verifycert

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

user

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

password

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

serial\_no

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

portgroup\_name

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

state

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

ports

![](RackMultipart20201029-4-4mjey4_html_d497e1f357883630.png)

port\_state

**Choice/default**

![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_d129f813cef34cc.png) ![](RackMultipart20201029-4-4mjey4_html_c4eeded2bb456dd.png)

- 91

- 92

- True

- False

![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png)

- absent

- present

![](RackMultipart20201029-4-4mjey4_html_8f7da4688f23f1c7.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png)

- present-in-group

- absent-in-group

**Comments**

![](RackMultipart20201029-4-4mjey4_html_d129f813cef34cc.png) ![](RackMultipart20201029-4-4mjey4_html_c4eeded2bb456dd.png)

IP or FQDN of the Unisphere host. This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The version of the Unisphere software.

This parameter is optional.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

To validate the SSL certificate.

- True - Verifies the SSL certificate.

- False - Specifies that the SSL certificate should not be verified.

This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The user name to access the Unisphere server. The user name can be encrypted using Ansible vault. This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The password to access the Unisphere server. The password can be encrypted using Ansible vault. This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The serial number of the PowerMax array. If this parameter is absent, the script lists all the serial numbers of the registered array on the specified Unisphere host. This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The name of the port group. The following conditions must be met when you enter the name:

- Do not use special characters except &quot;_\__.&quot;

- Case sensitive for RestAPI calls.

This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

Defines whether the port group must be present in the system.

- absent: The port group must not be present in the system.

- present: The port group must be present in the system.

This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

Lists the port director and ports that are added to the port group or removed from port group.

![](RackMultipart20201029-4-4mjey4_html_48a572954505821c.png)

Defines whether the port must be available in the port group.

- present-in-group: indicates that the port must be present in the port group.

**Ansible modules for Dell EMC PowerMax**** 37**

**Table 8. Parameters (continued)**

| **Parameter** |
 | **Choice/default** |
 | **Comments** |
 |
| --- | --- | --- | --- | --- | --- |
|
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 | ? absent-in-group: indicates that the |
 |
|
 |
 |
 |
 | port must not be present in the port |
 |
|
 |
 |
 |
 | group. |
 |
|
 |
 |
 |
 |
 |
 |
| new\_name |
 |
 |
 | The new name of the port group when |
 |
|
 |
 |
 |
 | you rename the port group. The |
 |
|
 |
 |
 |
 | following conditions must be met when |
 |
|
 |
 |
 |
 | you enter a new name: |
 |
|
 |
 |
 |
 | ? Do not use special characters except |
 |
|
 |
 |
 |
 | &quot;_\__.&quot; |
 |
|
 |
 |
 |
 | ? Case sensitive for RestAPI calls. |
 |
|
 |
 |
 |
 |
 |
 |

## **Masking View module**

The Masking View module manages the masking views on the PowerMax array.

The masking view module has the following functions:

- Create masking view with a port group, storage group, host, or host group.

- Modify masking view.

- Delete masking view.

For creating a masking view, the port groups, storage groups, hosts, and host groups must be present on the array. Once the masking view is created, only the name of the masking view can be changed. The entities such as port group, storage group, hosts, or host group cannot be changed. The masking view can be created either for a host or a host group, but not for both. The host name or a host group name must be provided to create masking view.

**Create masking view with host group**

The user can create a masking view with a host group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_1c3b622f4d628e4d.gif)

- name: Create MV with hostgroup dellemc\_powermax\_maskingview:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

mv\_name: &quot;{{mv\_name}}&quot;

portgroup\_name: &quot;Ansible\_Testing\_portgroup&quot;

hostgroup\_name: &quot;Ansible\_Testing\_hostgroup&quot;

sg\_name: &quot;Ansible\_Testing\_SG&quot;

state: &quot;present&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page40)for more information about the parameters.

**Create masking view with host**

The user can create a masking view with host by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_680ac7189a708599.gif)

- name: Create MV with host

**38**** Ansible modules for Dell EMC PowerMax**

dellemc\_powermax\_maskingview:

![](RackMultipart20201029-4-4mjey4_html_bcb60680fdfdeadd.gif)

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

mv\_name: &quot;{{mv\_name}}&quot;

portgroup\_name: &quot;Ansible\_Testing\_portgroup&quot;

host\_name: &quot;Ansible\_Testing\_host&quot;

sg\_name: &quot;Ansible\_Testing\_SG&quot;

state: &quot;present&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page40)for more information about the parameters.

**Rename masking view**

The user can rename the masking view by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_80462f446880980b.gif)

- name: Rename host masking view dellemc\_powermax\_maskingview:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

mv\_name: &quot;{{mv\_name}}&quot;

new\_mv\_name: &quot;Ansible\_Testing\_mv\_renamed&quot;

state: &quot;present&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page40)for more information about the parameters.

**Delete masking view**

The user can delete the masking view by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_7284e4285e2de4ab.gif)

- name: Delete host masking view dellemc\_powermax\_maskingview:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

mv\_name: &quot;Ansible\_Testing\_mv\_renamed&quot;

state: &quot;absent&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page40)for more information about the parameters.

**Ansible modules for Dell EMC PowerMax**** 39**

**Masking View module parameters**

The parameters for the Masking View module are listed as follows with an example:

**Table 9. Parameters**

![](RackMultipart20201029-4-4mjey4_html_71dfde8492fba241.png)

**Parameter**

![](RackMultipart20201029-4-4mjey4_html_d129f813cef34cc.png) ![](RackMultipart20201029-4-4mjey4_html_c4eeded2bb456dd.png)

unispherehost

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

universion

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

verifycert

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

user

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

password

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

serial\_no

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

mv\_name

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

new\_mv\_name

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

portgroup\_name

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

hostgroup\_name

![](RackMultipart20201029-4-4mjey4_html_d5c77acd64d8e1e5.png)

host\_name

**Choice/default**

![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_d129f813cef34cc.png) ![](RackMultipart20201029-4-4mjey4_html_c4eeded2bb456dd.png)

- 91

- 92

- True

- False

![](RackMultipart20201029-4-4mjey4_html_810686020a82da65.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png)

**Comments**

![](RackMultipart20201029-4-4mjey4_html_d129f813cef34cc.png) ![](RackMultipart20201029-4-4mjey4_html_c4eeded2bb456dd.png)

IP or FQDN of the Unisphere host. This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The version of the Unisphere software.

This parameter is optional.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

To validate the SSL certificate.

- True - Verifies the SSL certificate.

- False - Specifies that the SSL certificate should not be verified.

This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The user name to access the Unisphere server. The user name can be encrypted using Ansible vault. This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The password to access the Unisphere server. The password can be encrypted using Ansible vault. This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The serial number of the PowerMax array. If this parameter is absent, the script lists all the serial numbers of the registered array on the specified Unisphere host. This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The name of the masking view. The following conditions must be met when you enter the name:

- Do not use special characters except &quot;_\__.&quot;

- Case sensitive for RestAPI calls.

This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The new name of the masking view when you rename the existing masking view. The following conditions must be met when you provide the new name for masking view:

- Do not use special characters except &quot;_\__.&quot;

- Case sensitive for REST API calls.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The name of the existing port group.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The name of the existing host group. Use this parameter to create cluster export.

![](RackMultipart20201029-4-4mjey4_html_41a2f1d4c4331.png)

The name of the existing host. Use this parameter to create an exclusive host or to export to a host.

**40**** Ansible modules for Dell EMC PowerMax**

**Table 9. Parameters (continued)**

| **Parameter** |
 | **Choice/default** |
 | **Comments** |
 |
 |
| --- | --- | --- | --- | --- | --- | --- |
|
 |
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| sg\_name |
 |
 |
 |
 | The name of the existing storage group. |
 |
 |
| state |
 | ? | absent |
 | Defines whether the masking view must |
 |
 |
|
 |
 | ? | present |
 | be present on the system. This |
 |
 |
|
 |
 |
 | parameter is mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |

## **Snapshot module**

The Snapshot module manages the snapshots available on the PowerMax array.

The snapshot module has the following functions:

- Create a storage group snapshot.

- Get details of a storage group snapshot.

- Rename a storage group snapshot.

- Change storage group snapshot link status.

- Delete storage group snapshot.

**Create snapshot for a storage group**

The user can create a snapshot for a storage group by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_1c3b622f4d628e4d.gif)

- name: Create a Snapshot for a Storage Group dellemc\_powermax\_snapshot:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;ansible\_sg&quot;

snapshot\_name: &quot;ansible\_sg\_snap&quot;

ttl: &quot;2&quot;

ttl\_unit: &quot;days&quot;

state: &quot;present&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page43)for more information about the parameters.

**Get details of storage group snapshot**

The user can get details of a storage group snapshot by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_80462f446880980b.gif)

- name: Get Storage Group Snapshot details dellemc\_powermax\_snapshot:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;ansible\_sg&quot;

snapshot\_name: &quot;ansible\_sg\_snap&quot;

state: &quot;present&quot;

**Ansible modules for Dell EMC PowerMax**** 41**

The parameters must be set before the user runs the playbook. See the [Parameters table](#page43)for more information about the parameters.

**Delete storage group snapshot**

The user can delete a storage group snapshot by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_b8ead8090c2b170f.gif)

- name: Delete Storage Group Snapshot dellemc\_powermax\_snapshot:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;ansible\_sg&quot;

snapshot\_name: &quot;ansible\_sg\_snap&quot;

generation: 1

state: &quot;absent&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page43)for more information about the parameters.

**Rename storage group snapshot**

The user can rename the storage group snapshot by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_1c3b622f4d628e4d.gif)

- name: Rename Storage Group Snapshot dellemc\_powermax\_snapshot:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;ansible\_sg&quot;

snapshot\_name: &quot;ansible\_sg\_snap&quot;

new\_snapshot\_name: &quot;ansible\_snap\_new&quot;

generation: 0

state: &quot;present&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page43)for more information about the parameters.

**Change snapshot link status to linked**

The user can change the link status of the snapshot to _linked_ by running the appropriate playbook

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_aacaf59cfea37794.gif)

- name: Change Snapshot Link Status to Linked dellemc\_powermax\_snapshot:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;ansible\_sg&quot;

**42**** Ansible modules for Dell EMC PowerMax**

snapshot\_name: &quot;ansible\_snap\_new&quot;

![](RackMultipart20201029-4-4mjey4_html_52411522692c4f4d.gif)

generation: 1

target\_sg\_name: &quot;ansible\_sg\_target&quot;

link\_status: &quot;linked&quot;

state: &quot;present&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page43)for more information about the parameters.

**Change snapshot link status to unlinked**

The user can change the link status of the snapshot to _unlinked_ by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_ddfcea7564e4e812.gif)

- name: Change Snapshot Link Status to UnLinked dellemc\_powermax\_snapshot:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;ansible\_sg&quot;

snapshot\_name: &quot;ansible\_snap\_new&quot;

generation: 1

target\_sg\_name: &quot;ansible\_sg\_target&quot;

link\_status: &quot;unlinked&quot;

state: &quot;present&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page43)for more information about the parameters.

**Snapshot module parameters**

The parameters for the Snapshot module are listed as follows with an example:

**Table 10. Parameters**

| **Parameter** |
 | **Choice/default** |
 | **Comments** |
 |
 |
| --- | --- | --- | --- | --- | --- | --- |
|
 |
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| unispherehost |
 |
 |
 |
 | IP or FQDN of the Unisphere host. This |
 |
 |
|
 |
 |
 |
 |
 | parameter is mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| universion |
 | ? | 91 |
 | The version of the Unisphere software. |
 |
 |
|
 |
 | ? | 92 |
 | This parameter is optional. |
 |
 |
|
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| verifycert |
 | ? | True |
 | To validate the SSL certificate. |
 |
 |
|
 |
 | ? | False |
 | ? True - Verifies the SSL certificate. |
 |
 |
|
 |
 |
 |
 |
 | ? False - Specifies that the SSL |
 |
 |
|
 |
 |
 |
 |
 | certificate should not be verified. |
 |
 |
|
 |
 |
 |
 |
 | This parameter is mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| user |
 |
 |
 |
 | The user name to access the Unisphere |
 |
 |
|
 |
 |
 |
 |
 | server. The user name can be encrypted |
 |
 |
|
 |
 |
 |
 |
 | using Ansible vault. This parameter is |
 |
 |
|
 |
 |
 |
 |
 | mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| password |
 |
 |
 |
 | The password to access the Unisphere |
 |
 |
|
 |
 |
 |
 |
 | server. The password can be encrypted |
 |
 |
|
 |
 |
 |
 |
 | using Ansible vault. This parameter is |
 |
 |
|
 |
 |
 |
 |
 | mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |

**Ansible modules for Dell EMC PowerMax**** 43**

**Table 10. Parameters (continued)**

![](RackMultipart20201029-4-4mjey4_html_71dfde8492fba241.png)

**Parameter**

![](RackMultipart20201029-4-4mjey4_html_d129f813cef34cc.png) ![](RackMultipart20201029-4-4mjey4_html_c4eeded2bb456dd.png)

serial\_no

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

sg\_name

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

snapshot\_name

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

new\_snapshot\_name generation

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png) ![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

target\_sg\_name

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

link\_status

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

ttl

![](RackMultipart20201029-4-4mjey4_html_b641fab65f1dbc76.png)

ttl\_unit

![](RackMultipart20201029-4-4mjey4_html_a07884ab4b97cbcb.png)

state

**Choice/default**

![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_d129f813cef34cc.png) ![](RackMultipart20201029-4-4mjey4_html_c4eeded2bb456dd.png)

- linked

- unlinked

![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png) ![](RackMultipart20201029-4-4mjey4_html_e5ff6aff0a407e80.png)

- hours

- days

- absent

- present

![](RackMultipart20201029-4-4mjey4_html_4cc196ab5dfc3b4c.png)

**Comments**

![](RackMultipart20201029-4-4mjey4_html_d129f813cef34cc.png) ![](RackMultipart20201029-4-4mjey4_html_c4eeded2bb456dd.png)

The serial number of the PowerMax array. If this parameter is absent, the script lists all the serial numbers of the registered array on the specified Unisphere host. This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The name of the storage group. This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The name of the snapshot. This

parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The new name of the snapshot.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The generation number of the Snapshot. Generation is mandatory for link, unlink, rename, and delete operations. Optional for _Get snapshot details_ operation.

Create snapshot creates a snapshot with generation number 0. Rename is supported only for generation number 0.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The target storage group name.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

Defines the link status of the snapshot.

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The Time To Live (TTL) value for the Snapshot. If the TTL value is not specified, the storage group snapshot details would be returned. However, to create a storage group snapshot, the TTL must be specified. If the storage group snapshot does not have a TTL value, specify the TTL value as &quot;None.&quot;

![](RackMultipart20201029-4-4mjey4_html_e632c610dc632f4.png)

The unit for TTL. If no ttl\_unit is specified, &#39;days&#39; is taken as default value.

![](RackMultipart20201029-4-4mjey4_html_cb084fb9f45b335f.png)

Defines whether the snapshot must exist on the storage array. This parameter is mandatory.

## **SRDF Module**

The SRDF Module manages the SRDF links in Dell EMC PowerMax arrays. The SRDF Module supports the following functionalities:

- Create SRDF links with the following replication modes:

  - Synchronous

  - Asynchronous

  - Adaptive copy

  - Active mode

- Get SRDF pair states for a given storage group and RDFG number.

- Modify SRDF link mode.

- Perform the following operations:

  - Establish

  - Restore

**44**** Ansible modules for Dell EMC PowerMax**

  - Swap

  - Failover

  - Resume

  - Suspend

  - Split

  - Failback

  - Setbias

- Metro configurations: Set bias operation, change resiliency between bias and witness.

- Run create and update operations Asynchronously (by default) or synchronously.

- Get Job details for a given Job ID.

- Delete SRDF links.

- Concurrent SRDF configuration support.

- Online Device expansion support

![](RackMultipart20201029-4-4mjey4_html_79658bf8db97dce5.png)

![](RackMultipart20201029-4-4mjey4_html_b2348532066adb1b.png) **NOTE:** The following features are not supported:

![](RackMultipart20201029-4-4mjey4_html_9f619c1d7101a758.png) ![](RackMultipart20201029-4-4mjey4_html_7f58a03cf5cb64a7.png)

- The Star and Cascaded SRDF configurations

- The Invalidate, Ready, Not Ready, Move Pairs, and Refresh SRDF pairing operations

- Migration use cases through the SRDF Module

**Create SRDF links**

The user can create SRDF links by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_1c3b622f4d628e4d.gif)

- name: Create and establish storagegroup SRDF/S pairing dellemc\_powermax\_srdf:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

remote\_serial\_no: &quot;{{remote\_serial\_no}}&quot;

sg\_name: &quot;{{sg\_name}}&quot;

srdf\_mode: &#39;Synchronous&#39;

srdf\_state: &#39;Establish&#39;

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page51)for more information about the parameters.

**Create and establish a storage group SRDF/a pairing**

The user can create and establish a storage group SRDF/a pairing by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_71a836b7a09a9962.gif)

- name: Create and establish storagegroup SRDF/a pairing

register: Job\_details\_body dellemc\_powermax\_srdf:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;{{sg\_name}}&quot;

remote\_serial\_no: &quot;{{remote\_serial\_no}}&quot;

srdf\_mode: &#39;Asynchronous&#39;

**Ansible modules for Dell EMC PowerMax**** 45**

srdf\_state: &#39;Establish&#39;

![](RackMultipart20201029-4-4mjey4_html_680ac7189a708599.gif)

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page51)for more information about the parameters.

**Create a storage group SRDF/s pair in suspended mode**

The user can create a storage group SRDF/s pair in the default suspended mode by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_1c3b622f4d628e4d.gif)

- name: Create storagegroup SRDF/s pair in default suspended mode as an Synchronous task

dellemc\_powermax\_srdf:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;{{sg\_name2}}&quot;

remote\_serial\_no: &quot;{{remote\_serial\_no}}&quot;

state: &#39;present&#39;

srdf\_mode: &#39;Synchronous&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page51)for more information about the parameters.

**Get SRDF details**

The user can get SRDF details by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_7284e4285e2de4ab.gif)

- name: Get SRDF details dellemc\_powermax\_srdf:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;{{sg\_name}}&quot;

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page51)for more information about the parameters.

**Modify SRDF mode**

The user can modify SRDF mode by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_3e8be906193b9c44.gif)

- name: Modify SRDF mode dellemc\_powermax\_srdf:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

**46**** Ansible modules for Dell EMC PowerMax**

sg\_name: &quot;{{sg\_name}}&quot;

![](RackMultipart20201029-4-4mjey4_html_be4fc28e6ef0bfc0.gif)

srdf\_mode: &#39;Synchronous&#39;

state: &#39;present&#39;

You can modify the srdf\_mode parameter to any of the following modes:

- Synchronous

- Asynchronous

- Adaptive copy

- Active

The parameters must be set before the user runs the playbook. See the [Parameters table](#page51)for more information about the parameters.

**Failover SRDF link**

The user can perform failover operation by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_80462f446880980b.gif)

- name: Failover SRDF link dellemc\_powermax\_srdf:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;{{sg\_name}}&quot;

srdf\_state: &#39;Failover&#39;

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page51)for more information about the parameters.

**Failback SRDF link**

The user can perform failback operation by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_b8ead8090c2b170f.gif)

- name: Failback SRDF link dellemc\_powermax\_srdf:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{ serial\_no }}&quot;

sg\_name: &quot;{{sg\_name}}&quot;

rdfg\_no: &quot;{{rdfg\_no}}&quot;

srdf\_state: &quot;Failback&quot;

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page51)for more information about the parameters.

**Ansible modules for Dell EMC PowerMax**** 47**

**Create storage group Metro SRDF pair with Witness for resiliency**

The user can create a storage group Metro SRDF pair with Witness for resiliency by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_1c3b622f4d628e4d.gif)

- name: Create storagegroup Metro SRDF pair with Witness for resiliency dellemc\_powermax\_srdf:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;{{sg\_name}}&quot;

remote\_serial\_no: &quot;{{remote\_serial\_no}}&quot;

state: &#39;present&#39;

srdf\_mode: &#39;Active&#39;

srdf\_state: &#39;Establish&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page51)for more information about the parameters.

**Get SRDF Job status**

The user can get SRDF Job status by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_7284e4285e2de4ab.gif)

- name: Get SRDF Job status dellemc\_powermax\_srdf:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

job\_id: &quot;{{job\_id}}&quot;

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page51)for more information about the parameters.

**Establish SRDF link**

The user can establish the SRDF link by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_80462f446880980b.gif)

- name: Establish SRDF link dellemc\_powermax\_srdf:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;{{sg\_name}}&quot;

srdf\_state: &#39;Establish&#39;

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page51)for more information about the parameters.

**48**** Ansible modules for Dell EMC PowerMax**

**Create and Establish concurrent SRDF link**

The user can establish the concurrent SRDF link (one at a time) by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_92d0375e35378a12.gif)

- name: Create and Establish SRDF pairing with remote array 1 dellemc\_powermax\_srdf:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

remote\_serial\_no: &quot;{{remote\_serial\_no\_1}}&quot;

sg\_name: &quot;{{sg\_name}}&quot;

srdf\_state: &#39;Establish&#39;

srdf\_mode: &#39;Synchronous&#39;

state: &#39;present&#39;

- name: Create and Establish SRDF pairing with remote array 2 dellemc\_powermax\_srdf:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

remote\_serial\_no: &quot;{{remote\_serial\_no\_2}}&quot;

sg\_name: &quot;{{sg\_name}}&quot;

srdf\_state: &#39;Establish&#39;

srdf\_mode: &#39;Adaptive Copy&#39;

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page51)for more information about the parameters.

**Suspend SRDF link**

The user can suspend the SRDF link by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_80462f446880980b.gif)

- name: Suspend SRDF link dellemc\_powermax\_srdf:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;{{sg\_name2}}&quot;

srdf\_state: &#39;Suspend&#39;

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page51)for more information about the parameters.

**Ansible modules for Dell EMC PowerMax**** 49**

**Suspend concurrent SRDF link**

The user can suspend the concurrent SRDF link (one at a time) by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_80462f446880980b.gif)

- name: Suspend SRDF link dellemc\_powermax\_srdf:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;{{sg\_name2}}&quot;

srdf\_state: &#39;Suspend&#39;

state: &#39;present&#39;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page51)for more information about the parameters.

**Delete SRDF link**

The user can delete the SRDF links by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_7284e4285e2de4ab.gif)

- name: Delete SRDF link dellemc\_powermax\_srdf:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{serial\_no}}&quot;

sg\_name: &quot;{{sg\_name}}&quot;

state: &#39;absent&#39;

![](RackMultipart20201029-4-4mjey4_html_ccc782b327b61821.png) ![](RackMultipart20201029-4-4mjey4_html_e7ec2e65d5a2ee65.png) **NOTE:** Only links in Suspended states can be deleted.

![](RackMultipart20201029-4-4mjey4_html_7f58a03cf5cb64a7.png)

The parameters must be set before the user runs the playbook. See the [Parameters table](#page51)for more information about the parameters.

**Delete concurrent SRDF link**

The user can delete the concurrent SRDF link (one at a time) by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_b8ead8090c2b170f.gif)

- name: Delete SRDF link dellemc\_powermax\_srdf:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: &quot;{{r1\_serial\_no}}&quot;

sg\_name: &quot;{{sg\_name1}}&quot;

rdfg\_no: &quot;{{rdfGroupNumber}}&quot;

state: &#39;absent&#39;

wait\_for\_completion: True

**50**** Ansible modules for Dell EMC PowerMax**

![](RackMultipart20201029-4-4mjey4_html_b82eed0fc7d822f.png) ![](RackMultipart20201029-4-4mjey4_html_e7ec2e65d5a2ee65.png) **NOTE:** Only links in Suspended states can be deleted.

![](RackMultipart20201029-4-4mjey4_html_7f58a03cf5cb64a7.png)

The parameters must be set before the user runs the playbook. See the [Parameters table](#page51)for more information about the parameters.

**SRDF module parameters**

The following table provides information about the parameters that are displayed on the console, when the user runs the playbook using SRDF Module:

**Table 11. Parameters**

![](RackMultipart20201029-4-4mjey4_html_9be3bab8db1e9066.png)

**Parameter** unispherehost

![](RackMultipart20201029-4-4mjey4_html_3b433f4ae051eee9.png) ![](RackMultipart20201029-4-4mjey4_html_fcba516df8a58c08.png) ![](RackMultipart20201029-4-4mjey4_html_4e5c61c1e65a784e.png)

universion

![](RackMultipart20201029-4-4mjey4_html_3b433f4ae051eee9.png)

verifycert

![](RackMultipart20201029-4-4mjey4_html_3b433f4ae051eee9.png)

user

![](RackMultipart20201029-4-4mjey4_html_3b433f4ae051eee9.png)

password

![](RackMultipart20201029-4-4mjey4_html_3b433f4ae051eee9.png)

serial\_no

![](RackMultipart20201029-4-4mjey4_html_3b433f4ae051eee9.png)

remote\_serial\_no

![](RackMultipart20201029-4-4mjey4_html_3b433f4ae051eee9.png)

sg\_name

![](RackMultipart20201029-4-4mjey4_html_3b433f4ae051eee9.png)

srdf\_mode

![](RackMultipart20201029-4-4mjey4_html_501291b5a1a80aa7.png)

state

**Choices/default**

![](RackMultipart20201029-4-4mjey4_html_95be7fc2998bf586.png) ![](RackMultipart20201029-4-4mjey4_html_74b8b86965a4a4ed.png) ![](RackMultipart20201029-4-4mjey4_html_2b4283b1cafb2397.png)

- 91

- 92

- True

- False

![](RackMultipart20201029-4-4mjey4_html_95be7fc2998bf586.png) ![](RackMultipart20201029-4-4mjey4_html_95be7fc2998bf586.png) ![](RackMultipart20201029-4-4mjey4_html_95be7fc2998bf586.png) ![](RackMultipart20201029-4-4mjey4_html_95be7fc2998bf586.png) ![](RackMultipart20201029-4-4mjey4_html_95be7fc2998bf586.png) ![](RackMultipart20201029-4-4mjey4_html_95be7fc2998bf586.png) ![](RackMultipart20201029-4-4mjey4_html_95be7fc2998bf586.png)

- Active

- Adaptive Copy

- Synchronous

- Asynchronous

- present

- absent

![](RackMultipart20201029-4-4mjey4_html_c9549df544e5a4a8.png)

**Comments**

![](RackMultipart20201029-4-4mjey4_html_d55c9390551e4a7.png) ![](RackMultipart20201029-4-4mjey4_html_7177a33b31c5b33b.png)

IP or FQDN of the Unisphere host. This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_1efef89172a6ef75.png)

The version of the Unisphere software. This parameter is optional.

![](RackMultipart20201029-4-4mjey4_html_1efef89172a6ef75.png)

To validate the SSL certificate.

- True - indicates that the SSL certificate should be verified.

- False - indicates that the SSL certificate should not be verified.

This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_1efef89172a6ef75.png)

The username to access the Unisphere server. The username can be encrypted using Ansible vault. This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_1efef89172a6ef75.png)

The password to access the Unisphere server. The password can be encrypted using Ansible vault. This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_1efef89172a6ef75.png)

The serial number of the source PowerMax or VMAX array (primary array), when protecting a storage group. This parameter is mandatory. ![](RackMultipart20201029-4-4mjey4_html_5ad7bf5aeddf85f5.png) **NOTE:** You can issue srdf\_state operations

![](RackMultipart20201029-4-4mjey4_html_47a80e684edb2a7f.png) ![](RackMultipart20201029-4-4mjey4_html_df19a13595d7f13c.png)

from a primary or remote array.

![](RackMultipart20201029-4-4mjey4_html_1efef89172a6ef75.png)

1. 12-Digit serial number of the remote PowerMAX or VMAX array (remote). This parameter is mandatory when creating an SRDF pair.

![](RackMultipart20201029-4-4mjey4_html_1efef89172a6ef75.png)

Name of the Storage group. SRDF pairings are managed at a storage group level. This parameter is required to identify the SRDF link.

This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_1efef89172a6ef75.png)

The replication mode of the SRDF pair. This parameter is mandatory when creating an SRDF pair. It can be modified by specifying one of the following values:

- Active

- Adaptive Copy

- Synchronous

- Asynchronous

![](RackMultipart20201029-4-4mjey4_html_c4fe6791d0bc947a.png)

Define whether the SRDF pairing should exist or not.

**Ansible modules for Dell EMC PowerMax**** 51**

**Table 11. Parameters (continued)**

![](RackMultipart20201029-4-4mjey4_html_9be3bab8db1e9066.png)

**Parameter**

![](RackMultipart20201029-4-4mjey4_html_3b433f4ae051eee9.png) ![](RackMultipart20201029-4-4mjey4_html_fcba516df8a58c08.png) ![](RackMultipart20201029-4-4mjey4_html_4e5c61c1e65a784e.png)

srdf\_state

![](RackMultipart20201029-4-4mjey4_html_3b433f4ae051eee9.png)

new\_rdf\_group

![](RackMultipart20201029-4-4mjey4_html_3b433f4ae051eee9.png)

rdfg\_number

![](RackMultipart20201029-4-4mjey4_html_3b433f4ae051eee9.png)

job\_id

![](RackMultipart20201029-4-4mjey4_html_3b433f4ae051eee9.png)

wait\_for\_completion

![](RackMultipart20201029-4-4mjey4_html_cfe361acc4aea696.png)

witness

**Choices/default**

![](RackMultipart20201029-4-4mjey4_html_95be7fc2998bf586.png) ![](RackMultipart20201029-4-4mjey4_html_74b8b86965a4a4ed.png) ![](RackMultipart20201029-4-4mjey4_html_2b4283b1cafb2397.png)

- Establish

- Restore

- Swap

- Failover

- Resume

- Suspend

- Split

- Failback

- Setbias

- True

- False

![](RackMultipart20201029-4-4mjey4_html_95be7fc2998bf586.png)

The default value is false.

![](RackMultipart20201029-4-4mjey4_html_95be7fc2998bf586.png) ![](RackMultipart20201029-4-4mjey4_html_95be7fc2998bf586.png) ![](RackMultipart20201029-4-4mjey4_html_95be7fc2998bf586.png)

- True

- False

The default value is false.

![](RackMultipart20201029-4-4mjey4_html_cae5a7224af15c48.png)

- True

- False

**Comments**

![](RackMultipart20201029-4-4mjey4_html_d55c9390551e4a7.png) ![](RackMultipart20201029-4-4mjey4_html_7177a33b31c5b33b.png)

- present - indicate that the SRDF pairing should exist in the system.

- absent - indicate that the SRDF pairing should not exist in the system.

This parameter is mandatory.

![](RackMultipart20201029-4-4mjey4_html_1efef89172a6ef75.png)

Desired state of the SRDF pairing. This parameter is optional. While creating a new SRDF pair, the allowed values are **Establish** and **Suspend**. If the srdf\_ state parameter is not specified, the pair will be created in the **Suspend** state.

![](RackMultipart20201029-4-4mjey4_html_1efef89172a6ef75.png)

PowerMax has a limited number of RDF groups. If this flag is set to _True_, and the RDF groups are exhausted, then SRDF link creation will fail.

![](RackMultipart20201029-4-4mjey4_html_1efef89172a6ef75.png)

The RDF group number. This parameter is optional for each call. For the **create** operation, if specified, the array will reuse the RDF group, or display an error. For the **modify** and **delete** operations, if the RFD group number is not specified, the storage group is protected by multiple RDF Groups. This causes an error.

![](RackMultipart20201029-4-4mjey4_html_1efef89172a6ef75.png)

Job ID of an Asynchronous task. This parameter is used to get the details of a job.

![](RackMultipart20201029-4-4mjey4_html_1efef89172a6ef75.png)

Flag to indicate if the operation should be run synchronously or asynchronously.

- True - Synchronous

- False - Asynchronously

The default value is False. All create and update operations will be run asynchronously by default.

![](RackMultipart20201029-4-4mjey4_html_7fc82131d11e456a.png)

Flag to specify use of Witness for a Metro configuration. The flag can be set only for modifying the srdf\_state parameter to either Establish, Suspend or Restore.

- True - To use Witness

- False - To use Bias

![](RackMultipart20201029-4-4mjey4_html_5ad7bf5aeddf85f5.png) **NOTE:** It is recommended to set thisparameter for SRDF Metro in a production environment. Use _Unipshere for PowerMAX_ UI or REST API to configure this parameter.

![](RackMultipart20201029-4-4mjey4_html_5ad7bf5aeddf85f5.png) **NOTE:** Setwitnessto **true** when youcreate a Metro configuration.

**52**** Ansible modules for Dell EMC PowerMax**

## **RDF Group module**

The RDF Group module provides details of the RDF group and the list of volumes available on a specified RDF Group. The RDF group module supports the Get details of RDF Groups and volumes function.

**Get RDF group and volumes details**

The user can get details of an RDF group and the list of volumes in a specific RDF Group, by running the appropriate playbook.

The syntax of the playbook is shown as follows:

![](RackMultipart20201029-4-4mjey4_html_7284e4285e2de4ab.gif)

- name: Get RDF Group detail and Volumes dellemc\_powermax\_rdfgroup:

unispherehost: &quot;{{unispherehost}}&quot;

universion: &quot;{{universion}}&quot;

verifycert: &quot;{{verifycert}}&quot;

user: &quot;{{user}}&quot;

password: &quot;{{password}}&quot;

serial\_no: {{ serial\_no }}

rdfgroup\_number: &quot;{{rdfgroup\_number}}&quot; register: &quot;rdfgroup\_result&quot;

The parameters must be set before the user runs the playbook. See the [Parameters table](#page53)for more information about the parameters.

**RDF Group module parameters**

The parameters for the RDF Group module are listed as follows with an example:

**Table 12. Parameters**

| **Parameter** |
 | **Choice/default** |
 | **Comments** |
 |
 |
| --- | --- | --- | --- | --- | --- | --- |
|
 |
 |
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| unispherehost |
 |
 |
 |
 | IP or FQDN of the Unisphere host. This |
 |
 |
|
 |
 |
 |
 |
 | parameter is mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| universion |
 | ? | 91 |
 | The version of the Unisphere software. |
 |
 |
|
 |
 | ? | 92 |
 | This parameter is optional. |
 |
 |
|
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| verifycert |
 | ? | True |
 | To validate the SSL certificate. |
 |
 |
|
 |
 | ? | False |
 | ? True - Verifies the SSL certificate. |
 |
 |
|
 |
 |
 |
 |
 | ? False - Specifies that the SSL |
 |
 |
|
 |
 |
 |
 |
 | certificate should not be verified. |
 |
 |
|
 |
 |
 |
 |
 | This parameter is mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| user |
 |
 |
 |
 | The username to access the Unisphere |
 |
 |
|
 |
 |
 |
 |
 | server. The username can be encrypted |
 |
 |
|
 |
 |
 |
 |
 | using Ansible vault. This parameter is |
 |
 |
|
 |
 |
 |
 |
 | mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| password |
 |
 |
 |
 | The password to access the Unisphere |
 |
 |
|
 |
 |
 |
 |
 | server. The password can be encrypted |
 |
 |
|
 |
 |
 |
 |
 | using Ansible vault. This parameter is |
 |
 |
|
 |
 |
 |
 |
 | mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |
| serial\_no |
 |
 |
 |
 | The serial number of the PowerMax |
 |
 |
|
 |
 |
 |
 |
 | array. If this parameter is absent, the |
 |
 |
|
 |
 |
 |
 |
 | script lists all the serial numbers of the |
 |
 |
|
 |
 |
 |
 |
 | registered array on the specified |
 |
 |
|
 |
 |
 |
 |
 | Unisphere host. This parameter is |
 |
 |
|
 |
 |
 |
 |
 | mandatory. |
 |
 |
|
 |
 |
 |
 |
 |
 |
 |
 |

**Ansible modules for Dell EMC PowerMax**** 53**

**Table 12. Parameters (continued)**

| **Parameter** |
 | **Choice/default** |
 | **Comments** |
 |
| --- | --- | --- | --- | --- | --- |
|
 |
 |
 |
 |
 |
 |
|
 |
 |
 |
 |
 |
 |
| rdfgroup\_number |
 |
 |
 | The serial number of the RDF Group, |
 |
|
 |
 |
 |
 | used to get the details of an RDF Group |
 |
|
 |
 |
 |
 | and list the volumes of the specified RDF |
 |
|
 |
 |
 |
 | Group. |
 |
|
 |
 |
 |
 |
 |
 |

**54**** Ansible modules for Dell EMC PowerMax**
