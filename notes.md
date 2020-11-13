-   [Revision history](#revision-history)
-   [Product description](#product-description)
-   [○ Delete snapshot schedule Known problems and
    limitations](#delete-snapshot-schedule-known-problems-and-limitations)
    -   [Limitations and
        considerations](#limitations-and-considerations)
-   [Additional resources](#additional-resources)
    -   [Documentation](#documentation)
    -   [Troubleshoot and get help](#troubleshoot-and-get-help)
        -   [Technical support](#technical-support)

Ansible Modules for Dell EMC Unity

Version 1.0

Release Notes

Rev. 01

June 2020

These release notes contain supplemental information about Ansible
Modules for Dell EMC Unity and include the following topics:

-   Revision
    history...........................................................................................................................................................................................................2

-   Product
    description....................................................................................................................................................................................................2

-   New
    features...............................................................................................................................................................................................................2

-   Known problems and
    limitations...............................................................................................................................................................................3

-   Software media, organization, and
    files...................................................................................................................................................................4

-   Additional
    resources...................................................................................................................................................................................................
    4

Revision history
================

The table in this section lists the revision history of this document.

Table 1. Revision History

| Revision | Date      | Description                     |
|----------|-----------|---------------------------------|
| 01       | June 2020 | Initial release of the product. |

Product description
===================

Learn about Ansible Modules for Dell EMC Unity and the supported
features.

The Ansible modules for Dell EMC Unity are used to automate and
orchestrate the deployment, configuration, and management of Dell

EMC Unity Family systems, including Unity, Unity XT, and the UnityVSA.
The capabilities of Ansible modules are managing volumes (LUNs),
consistency groups, storage pools, hosts, snapshots, and snapshot
schedules, and obtaining Unity system information. The options available
for each capability are list, show, create, delete, and modify. New
features

List of features that are supported in this release.

The Ansible Modules for Dell EMC Unity Version 1.0 initial release
supports the following tasks for block-based storage:

-   Gather Facts Module

    1.  List of volumes

> ○ List of consistency groups
>
> ○ List of fibre channel (FC) initiators
>
> ○ List of iSCSI initiators
>
> ○ List of hosts
>
> ○ List of snapshot schedules

-   Volume Module (LUNs) ○ Create volume

▪ In a pool

▪ Assign an I/O limit policy

▪ Assign a tiering policy

▪ Assign a snap schedule

▪ Map to a host

1.  Modify Volume

▪ Expand a volume by name or ID

▪ Modify volume details including description, compression, and default
SP

▪ Modify host by volume name or ID

▪ Modify host mapping by host name or host ID

> ○ Delete volume

▪ Delete a volume by volume name or ID

-   Consistency Group Module

    1.  Create a consistency group

> ○ Get details for a consistency group by consistency group name or ID
>
> ○ Add volumes to a consistency group
>
> ○ Modify consistency group details
>
> ○ Rename a consistency group
>
> ○ Remove volumes (LUNs) from a consistency group
>
> ○ Delete a consistency group

-   Storage Pool Module

    1.  Get storage pool details using a pool name or pool ID

> ○ Modify storage pool attributes using the pool name or pool ID

2 Ansible Modules for Dell EMC Unity

-   Host Module

    1.  Create a host

> ○ Create a host with FC or iSCSI initiators
>
> ○ Add FC or iSCSI initiators to a host
>
> ○ Get details of a host
>
> ○ Modify host attributes
>
> ○ Rename a host
>
> ○ Remove FC and iSCSI initiators from a host
>
> ○ Delete a host

-   Snapshot Module

    1.  Create a snapshot for a consistency group

> ○ Create a snapshot for a volume (LUN)
>
> ○ Get snapshot details
>
> ○ Map a host to a snapshot
>
> ○ Unmap a host from a snapshot
>
> ○ Modify attributes of a snapshot for a volume (LUN)
>
> ○ Delete a snapshot

-   Snapshot Schedule Module

    1.  Create a snapshot schedule with an hourly rule

> ○ Create a snapshot schedule with a daily rule
>
> ○ Create a snapshot schedule with an every n days rule
>
> ○ Create a snapshot schedule with a weekly rule
>
> ○ Create a snapshot schedule with a monthly rule
>
> ○ Get details of a specific snapshot schedule
>
> ○ Modify the attributes of a snapshot schedule

○ Delete snapshot schedule Known problems and limitations
=========================================================

List of known problems and limitations for the Ansible Modules for Dell
EMC Unity version 1.0 release.

Known problems

There are no known problems in this release.

Limitations and considerations
------------------------------

Note the following considerations when using Ansible Modules for Dell
EMC Unity 1.0:

-   Storage pools module

    1.  Only the get and modify operations are supported in this
        > release.

> ○ The create and delete operations are not applicable in 1.0.

-   Consistency groups module

    1.  If a consistency group has snapshots, you cannot add or remove
        > volumes from it.

> ○ Consistency groups cannot be mapped to a host. Only the individual
> volumes (LUNs) that comprise the consistency group can be mapped to a
> host.
>
> ○ If a consistency group has volumes, it cannot be deleted.
>
> ○ Tiering policies cannot be applied to an empty consistency group.

-   Volumes module

    1.  You cannot delete a volume that has mapped hosts.

> ○ You must first unmap the hosts using the unmap operation for any
> volumes you need to delete.

-   Snapshot schedules module

    1.  Snapshot schedules created using Ansible can only have one rule
        > applied. ○ For the create and modify operations, the type is
        > mandatory.

Ansible Modules for Dell EMC Unity 3

> ○ You cannot modify a rule type once the schedule is created. However,
> you can modify other parameters within the same rule type. ○ A rule
> cannot have both autodelete and a desired retention time set at the
> same time. These parameters are mutually exclusive.
>
> ○ If an existing snapshot schedule has more than one rule applied to
> it, only the get and delete operations are available when using
> Ansible for those snapshots schedules.

-   Host module

    1.  Host initiators can only be removed when they are in a logged
        > off state, meaning, there are no active initiator paths
        > associated with the initiator. Software media, organization,
        > and files

This section provides information about where to find the software files
for this release of the product.

The software package is available for download from the
<https://github.com/dell/ansible-unity> page.

Additional resources
====================

Learn how to find more information about the product and get support.

Documentation
-------------

This section lists the related documentation for Ansible Modules for
Dell EMC Unity..

The latest documentation for Ansible Modules for Dell EMC Unity is
available on the
[https://github.com/dell/ansible-unity](https://GITHUB.COM/DELL/ANSIBLE-UNITY)
page. This documentation includes the following:

-   Ansible Modules for Dell EMC Unity Release Notes (this document)

-   Ansible Modules for Dell EMC Unity Product Guide

Troubleshoot and get help
-------------------------

Use the resources in this topic to get help and support.

### Technical support

Ansible modules for Unity are supported by Dell EMC, and are provided
under the terms of the license that is attached to the source code. Dell
EMC does not provide support for any source code modifications.

For Ansible configuration, setup issues, or questions, use the [Dell EMC
Automation
community](https://www.dell.com/community/Automation/bd-p/Automation).
For any issues with Dell EMC Storage, contact [Dell EMC Online
Support](https://www.dell.com/support).

4 Ansible Modules for Dell EMC Unity

#### Notes, cautions, and warnings

> NOTE: A NOTE indicates important information that helps you make
> better use of your product.
>
> CAUTION: A CAUTION indicates either potential damage to hardware or
> loss of data and tells you how to avoid the problem.
>
> WARNING: A WARNING indicates a potential for property damage, personal
> injury, or death.

© 2020 Dell Inc. or its subsidiaries. All rights reserved. Dell, EMC,
and other trademarks are trademarks of Dell Inc. or its subsidiaries.
Other trademarks may be trademarks of their respective owners.
