
SELECT ID, FISH_NAME, LENGTH
FROM
    (SELECT TOP_RANK.ID, N.FISH_NAME, TOP_RANK.LENGTH
    FROM
    (
    (SELECT FISH_INFO.ID, FISH_INFO.FISH_TYPE, FISH_INFO.LENGTH
    FROM (FISH_INFO JOIN
        (SELECT FISH_TYPE, MAX(LENGTH) AS LENGTH
        FROM FISH_INFO
        GROUP BY FISH_TYPE) AS STATS ON FISH_INFO.FISH_TYPE = STATS.FISH_TYPE AND FISH_INFO.LENGTH = STATS.LENGTH)) AS TOP_RANK
    JOIN FISH_NAME_INFO AS N
    ON TOP_RANK.FISH_TYPE = N.FISH_TYPE
        )) AS RET
ORDER BY ID;