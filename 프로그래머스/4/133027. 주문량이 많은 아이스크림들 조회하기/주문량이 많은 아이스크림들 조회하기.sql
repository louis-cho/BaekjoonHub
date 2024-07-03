SELECT DISTINCT T.FLAVOR
FROM (SELECT F.FLAVOR, SUM(F.TOTAL_ORDER + J.TOTAL_ORDER) AS TOTAL_ORDER
      FROM FIRST_HALF F
      JOIN JULY J ON F.FLAVOR = J.FLAVOR
     GROUP BY (FLAVOR)) AS T
ORDER BY T.TOTAL_ORDER DESC
LIMIT 3;