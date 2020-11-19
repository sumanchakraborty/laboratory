-   [Synopsis](#synopsis)
-   [Requirements](#requirements)
-   [Parameters](#parameters)
-   [Notes](#notes)
-   [Examples](#examples)
-   [Return Values](#return-values)
    -   [Authors](#authors)

<u>Docs</u> (<u>../../../index.html)</u> »
dellemc.unity.dellemc\_unity\_host – Manage Host operations on Unity.

> You are reading an older version of the Ansible documentation. Use the
> version selection to the left if you want the latest stable released
> version.

dellemc.unity.dellemc\_unity\_host – Manage Host operations on Unity.

>  **Note**
>
> This module is part of ansible-base and included in all Ansible
> installations. In most cases, you can use the short module name
> dellemc\_unity\_host even without specifying the collections: keyword.
> Despite that, we recommend you use the FQCN for easy linking to the
> module documentation and to avoid con icting with other collections
> that may have the same module name.

*New in version 1.1.0:* of dellemc.unity

> <u>S</u>y<u>nopsis</u>
>
> <u>Requirements</u>
>
> <u>Parameters</u>
>
> <u>Notes</u>
>
> <u>Examples Return Values</u>

Synopsis
========

> Creation of a Host.
>
> Addition of initiators to Host.
>
> Removal of initiators from Host.
>
> Modi cation of host attributes.
>
> Get details of a Host.
>
> Deletion of a Host.

Requirements
============

The below requirements are needed on the host that executes this module.

> A DellEMC Unity Storage device.
>
> Ansible 2.9 or higher.

Parameters
==========

<table>
<thead>
<tr class="header">
<th><blockquote>
<p><strong>Parameter</strong></p>
</blockquote></th>
<th><blockquote>
<p><strong>Choices/Defaults</strong></p>
</blockquote></th>
<th><blockquote>
<p><strong>Comments</strong></p>
</blockquote></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p><strong>description</strong></p>
<p>string</p></td>
<td></td>
<td>Host description.</td>
</tr>
<tr class="even">
<td><p><strong>host_id</strong></p>
<p>string</p></td>
<td></td>
<td><p>Unique identi er of the host.</p>
<p>host_id is auto generated during creation.</p>
<p>Except create, all other operations require either host_id or host_name.</p></td>
</tr>
<tr class="odd">
<td><p><strong>host_name</strong></p>
<p>string</p></td>
<td></td>
<td><p>Name of the host.</p>
<p>Mandatory for host creation.</p></td>
</tr>
<tr class="even">
<td><p><strong>host_os</strong></p>
<p>string</p></td>
<td><p><strong>Choices:</strong></p>
<blockquote>
<p>AIX</p>
<p>Citrix</p>
<p>XenServer</p>
<p>HP-UX</p>
<p>IBM VIOS</p>
<p>Linux</p>
<p>Mac OS</p>
<p>Solaris</p>
<p>VMware ESXi</p>
<p>Windows</p>
<p>Client</p>
</blockquote>
<p>Windows</p>
<blockquote>
<p>Server</p>
</blockquote></td>
<td>Operating system running on the host.</td>
</tr>
<tr class="odd">
<td><strong>initiator_state</strong> string</td>
<td><strong>Choices:</strong> present-inhost absent-inhost</td>
<td>State of the initiator.</td>
</tr>
<tr class="even">
<td><strong>initiators</strong> list / elements=string</td>
<td></td>
<td>List of initiators to be added/removed to/from host.</td>
</tr>
<tr class="odd">
<td><p><strong>new_host_name</strong></p>
<p>string</p></td>
<td></td>
<td><p>New name for the host.</p>
<p>Only required in rename host operation.</p></td>
</tr>
<tr class="even">
<td><p><strong>password</strong></p>
<p>string / required</p></td>
<td></td>
<td>the password of the Unity management server.</td>
</tr>
<tr class="odd">
<td><strong>port</strong> integer</td>
<td><p><strong>Default:</strong></p>
<p>443</p></td>
<td>Port number through which communication happens with Unity management server.</td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
</tr>
<tr class="odd">
<td><p><strong>state</strong></p>
<p>string / required</p></td>
<td><strong>Choices:</strong> present absent</td>
<td>State of the host.</td>
</tr>
<tr class="even">
<td><p><strong>unispherehost</strong></p>
<p>string / required</p></td>
<td></td>
<td>IP or FQDN of the Unity management server.</td>
</tr>
<tr class="odd">
<td><p><strong>username</strong></p>
<p>string / required</p></td>
<td></td>
<td>username of the Unity management server.</td>
</tr>
<tr class="even">
<td><strong>verifycert</strong> boolean</td>
<td><strong>Choices:</strong> no <strong>yes</strong> ←</td>
<td><p>Boolean variable to specify whether or not to validate SSL certi cate.</p>
<p>True - Indicates that the SSL certi cate should be veri ed.</p>
<p>False - Indicates that the SSL certi cate should not be veri ed.</p></td>
</tr>
</tbody>
</table>

Notes
=====

>  **Note**
>
> The modules pre xed with dellemc\_unity are built to support the
> DellEMC Unity storage platform.

Examples
========

<table>
<thead>
<tr class="header">
<th><ul>
<li><p>name<strong>:</strong> Create empty Host. dellemc_unity_host<strong>:</strong></p></li>
</ul>
<p>unispherehost<strong>:</strong> "{{<strong>unispherehost</strong>}}" username<strong>:</strong> "{{<strong>username</strong>}}" password<strong>:</strong> "{{<strong>password</strong>}}" verifycert<strong>:</strong> "{{<strong>verifycert</strong>}}" host_name<strong>:</strong> "ansible-test-host" host_os<strong>:</strong> "Linux" description<strong>:</strong> "ansible-test-host" state<strong>:</strong> "present"</p>
<ul>
<li><p>name<strong>:</strong> Create Host with Initiators. dellemc_unity_host<strong>:</strong></p></li>
</ul>
<p>unispherehost<strong>:</strong> "{{<strong>unispherehost</strong>}}" username<strong>:</strong> "{{<strong>username</strong>}}" password<strong>:</strong> "{{<strong>password</strong>}}" verifycert<strong>:</strong> "{{<strong>verifycert</strong>}}" host_name<strong>:</strong> "ansible-test-host-1" host_os<strong>:</strong> "Linux" description<strong>:</strong> "ansible-test-host-1" initiators<strong>:</strong></p>
<ul>
<li><p>"iqn.1994-05.com.redhat:c38e6e8cfd81"</p></li>
<li><p>"20:00:00:90:FA:13:81:8D:10:00:00:90:FA:13:81:8D" initiator_state<strong>:</strong> "present-in-host" state<strong>:</strong> "present"</p></li>
<li><p>name<strong>:</strong> Modify Host using host_id. dellemc_unity_host<strong>:</strong></p></li>
</ul>
<p>unispherehost<strong>:</strong> "{{<strong>unispherehost</strong>}}" username<strong>:</strong> "{{<strong>username</strong>}}" password<strong>:</strong> "{{<strong>password</strong>}}" verifycert<strong>:</strong> "{{<strong>verifycert</strong>}}" host_id<strong>:</strong> "Host_253" new_host_name<strong>:</strong> "ansible-test-host-2" host_os<strong>:</strong> "Mac OS" description<strong>:</strong> "Ansible tesing purpose" state<strong>:</strong> "present"</p>
<ul>
<li><p>name<strong>:</strong> Add Initiators to Host. dellemc_unity_host<strong>:</strong></p></li>
</ul>
<p>unispherehost<strong>:</strong> "{{<strong>unispherehost</strong>}}" username<strong>:</strong> "{{<strong>username</strong>}}" password<strong>:</strong> "{{<strong>password</strong>}}" verifycert<strong>:</strong> "{{<strong>verifycert</strong>}}" host_name<strong>:</strong> "ansible-test-host-2" initiators<strong>:</strong></p>
<ul>
<li><p>"20:00:00:90:FA:13:81:8C:10:00:00:90:FA:13:81:8C" initiator_state<strong>:</strong> "present-in-host" state<strong>:</strong> "present"</p></li>
<li><p>name<strong>:</strong> Get Host details using host_name. dellemc_unity_host<strong>:</strong></p></li>
</ul>
<p>unispherehost<strong>:</strong> "{{<strong>unispherehost</strong>}}" username<strong>:</strong> "{{<strong>username</strong>}}" password<strong>:</strong> "{{<strong>password</strong>}}" verifycert<strong>:</strong> "{{<strong>verifycert</strong>}}" host_name<strong>:</strong> "ansible-test-host-2" state<strong>:</strong> "present"</p>
<ul>
<li><p>name<strong>:</strong> Get Host details using host_id. dellemc_unity_host<strong>:</strong></p></li>
</ul>
<p>unispherehost<strong>:</strong> "{{<strong>unispherehost</strong>}}"</p></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p>username<strong>:</strong> "{{<strong>username</strong>}}" password<strong>:</strong> "{{<strong>password</strong>}}" verifycert<strong>:</strong> "{{<strong>verifycert</strong>}}" host_id<strong>:</strong> "Host_253" state<strong>:</strong> "present"</p>
<p><strong>-</strong> name<strong>:</strong> Delete Host. dellemc_unity_host<strong>:</strong></p>
<p>unispherehost<strong>:</strong> "{{<strong>unispherehost</strong>}}" username<strong>:</strong> "{{<strong>username</strong>}}" password<strong>:</strong> "{{<strong>password</strong>}}" verifycert<strong>:</strong> "{{<strong>verifycert</strong>}}" host_name<strong>:</strong> "ansible-test-host-2" state<strong>:</strong> "absent"</p></td>
</tr>
</tbody>
</table>

Return Values
=============

Common return values are documented <u>here</u>

<u>(../../../reference\_appendices/common\_return\_values.html\#common-return-values)</u>,
the following are the elds unique to this module:

<table>
<thead>
<tr class="header">
<th><blockquote>
<p><strong>Key</strong></p>
</blockquote></th>
<th><blockquote>
<p><strong>Returned</strong></p>
</blockquote></th>
<th><blockquote>
<p><strong>Description</strong></p>
</blockquote></th>
<th></th>
<th></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p><strong>changed</strong></p>
<p>boolean</p></td>
<td>always</td>
<td>Whether or not the resource has changed.</td>
<td></td>
<td></td>
</tr>
<tr class="even">
<td><strong>host_details</strong> complex</td>
<td>When host exists.</td>
<td>Details of the host.</td>
<td></td>
<td></td>
</tr>
<tr class="odd">
<td></td>
<td><p><strong>description</strong></p>
<p>string</p></td>
<td>success</td>
<td>Description about the host.</td>
<td></td>
</tr>
<tr class="even">
<td></td>
<td><strong>fc_host_initiators</strong> complex</td>
<td>success</td>
<td>Details of the FC initiators associated with the host.</td>
<td></td>
</tr>
<tr class="odd">
<td></td>
<td></td>
<td><p><strong>UnityHostInitiatorList</strong></p>
<p>complex</p></td>
<td>success</td>
<td>FC initiators with system generated unique hash value.</td>
</tr>
<tr class="even">
<td></td>
<td><strong>id</strong> string</td>
<td>success</td>
<td>The system ID given to the host.</td>
<td></td>
</tr>
<tr class="odd">
<td></td>
<td><strong>iscsi_host_initiators</strong> complex</td>
<td>success</td>
<td>Details of the ISCSI initiators associated with the host.</td>
<td></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td><p><strong>UnityHostInitiatorList</strong></p>
<p>complex</p></td>
<td>success</td>
<td>ISCSI initiators with sytem genrated unique hash value.</td>
</tr>
<tr class="odd">
<td></td>
<td><p><strong>name</strong></p>
<p>string</p></td>
<td>success</td>
<td>The name of the host.</td>
<td></td>
</tr>
<tr class="even">
<td></td>
<td><p><strong>os_type</strong></p>
<p>string</p></td>
<td>success</td>
<td>Operating system running on the host.</td>
<td></td>
</tr>
<tr class="odd">
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
</tr>
<tr class="even">
<td></td>
<td><p><strong>type</strong></p>
<p>string</p></td>
<td>success</td>
<td>HostTypeEnum of the host.</td>
<td></td>
</tr>
</tbody>
</table>

Authors
-------

Rajshree Khare (@kharer5) &lt;<u>ansible.team</u>@<u>dell.com</u>
(<u>mailto:ansible.team%40dell.com)</u>&gt;
