Steps taken in order to generate the input prefixes file:

    1. Download routes from (Aggregation using prepended AS Path/BGP Path):
        http://bgp.potaroo.net/as6447/bgp-table-asppath.txt

    2. Command to delete withdrawn routes:
        $ sed '/Withdrawn/d' bgp-table-asppath.txt > as6447_nowithdrawn.txt

    3. Delete everything from the resulting file, except the routes in the first
       column. 

    4. Remove repeated prefixes/routes:
        $ awk '!a[$0]++' as6447_prefixes.txt

    5. Add dummy next hop IP addresses in the second column (eg.: 192.168.0.1).

