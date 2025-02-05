SELECT ITEM_ID, ITEM_NAME, RARITY
FROM (SELECT I.ITEM_ID, I.ITEM_NAME, I.RARITY, T.PARENT_ITEM_ID
      FROM ITEM_INFO I JOIN ITEM_TREE T ON I.ITEM_ID = T.ITEM_ID) AS RET
WHERE RET.PARENT_ITEM_ID IN (
    SELECT ITEM_ID
    FROM ITEM_INFO
    WHERE RARITY = 'RARE'
)
ORDER BY ITEM_ID DESC;